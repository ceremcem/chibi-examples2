/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#include "ch.h"
#include "hal.h"
/*#include "rt_test_root.h"
#include "oslib_test_root.h"*/

#define BUFFER_LENGTH 16

SerialConfig sConfig = 
{
	115200,
	0,
	USART_CR2_CLKEN | USART_CR2_STOP1_BITS | USART_CR2_LINEN,
	0
};


uint8_t calculateFCS(uint8_t *buffer, uint8_t count);
uint8_t getData(uint8_t *buffer, uint8_t count);
void prepareFrame(uint8_t *to_send, uint8_t *received, uint8_t length);


int main(void)
{

	/*
	* System initializations.
	* - HAL initialization, this also initializes the configured device drivers
	*   and performs the board-specific initializations.
	* - Kernel initialization, the main() function becomes a thread and the
	*   RTOS is active.
	*/
	halInit();
	chSysInit();
	
	uint8_t buffer[8] = {0,0,0,0,0,0,0,0};
	uint8_t send_buffer[8];
	uint8_t send_length;
	
	/* USART 2
	 * A2 - TX
	 * A3 - RX*/
	/*done in board.h why not here..*/
	/*palSetPadMode(GPIOA, 2, 0xB);*/
	/*palSetPadMode(GPIOA, 3, 0x8);*/
	
	
	/*Pin of built in led*/
	palSetPadMode(GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL);
	
	
	sdStart(&SD2, NULL);

	
	/*chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO+1, Thread1, NULL);*/
	
	
	while(!0)
	{
		sdRead(&SD2, buffer, 1);
		if(0x1 == buffer[0] && getData(buffer, 3))
		{
			/*output set */
			send_length = 4;
			prepareFrame(send_buffer, buffer, 3);
			uint16_t output_data = (buffer[1] << 8) | buffer[2];
			/*for debug*/
			if(0xFFFF == output_data)
				palSetPad(GPIOC, 13);
			else
				palClearPad(GPIOC, 13);
				
			//palWritePort(GPIOB, output_data);
			GPIOB->ODR = output_data;
		}
		else if(0x2 == buffer[0] && getData(buffer, 1))
		{
			/*output get */
			send_length = 4;
			prepareFrame(send_buffer, buffer, 1);
			uint16_t data_on_output;
			data_on_output = GPIOB->ODR & 0x0000FFFF;
			send_buffer[2] = (data_on_output & 0xFF00) >> 8;
			send_buffer[3] = data_on_output & 0x00FF;
		}
		else if(0x3 == buffer[0] && getData(buffer, 1))
		{
			/*input get */
			prepareFrame(send_buffer, buffer, 2);
			send_length = 3;
			uint8_t input_data= GPIOA->IDR & 0x0003;
			send_buffer[2] = input_data;
		}
		else if(0x4 == buffer[0] && getData(buffer, 4))
		{
			/*rgb set */
			prepareFrame(send_buffer, buffer, 4);
			send_length = 4;
		}
		else if(0x5 == buffer[0] && getData(buffer, 1))
		{
			/*therm get */
			prepareFrame(send_buffer, buffer, 1);
			send_length = 1;
		}
		else if(0x6 == buffer[0] && getData(buffer, 2))
		{
			/*motor val set*/
			prepareFrame(send_buffer, buffer, 2);
			send_length = 2;
		}
		else 
		{
			/*invalid frame*/
			continue;
		}
		
		send_buffer[send_length] = calculateFCS(send_buffer, send_length);
		send_length++;/*crc added to end*/
		sdWrite(&SD2, send_buffer, send_length);
	}
}

void prepareFrame(uint8_t *to_send, uint8_t *received, uint8_t length)
{
	uint8_t i;
	to_send[0] = 0x55;/*ACK*/
	for(i = 0; i < length; i++)
	{
		to_send[i+1] = received[i];
	}
	return;
}

uint8_t getData(uint8_t *buffer, uint8_t count)
{
	sdRead(&SD2, &(buffer[1]), count);
	uint8_t crc = calculateFCS(buffer, count);
	return (crc == buffer[count]);
}

uint8_t calculateFCS(uint8_t *buffer, uint8_t count)
{
	uint8_t val, i;
	val = 0;
	for(i = 0; i < count; i++)
	{
		val = val ^ buffer[i];
	}
	return val;
}

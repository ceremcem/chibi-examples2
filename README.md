Fetching
--------------------

    git clone --recurse https://aktos.io/git/efecanicoz/io-expander2

Flashing and debugging
---------------------

Basic instructions:

1. Flashing                    : `make write`
2. Debugging:
    1. Start a session         : `make create-debug-session`
    2. Start your debugger     : `make debug-cmd` (or `make debug-gui-...`)

For further instructions, see mcu-debug/README.md

BOARD INFO:
------
	Pinout:
		A0:input1
		A1:input2
		A2:TX
		A3:RX
		A4..A7:ADCIN
		A8..A10:RGB led outputs
		A11:Motor output

		B0-B15: output pins

		C0: motherboard control pin


COMMUNICATION SETTINGS:
--------------

Serial Port Settings: 38400baud, 8N1

STARTUP:
------
	At power on mcu waits for 2 seconds
	sets C0 to 0
	waits 200 ms
	sets C0 to 1
	waits 200 ms
	sets C0 to 0

	after this sequence mcu expect to receive 0x(cafebabedeadbeef) if this message received then mcu sends 0x(deadbeefcafebabe) back
		otherwise power on sequence is repeated


MESSAGE PROTOCOL:
------

### Request/Response

	`01`: Set output pins:
		Send: 		0x01 <2 byte pin states> CRC
		Expect: 	0x55 0x01 <2 byte pin states> CRC

	`02`: Get output pins:
		Send: 		0x02 CRC
		Expect: 	0x55 0x02 <2 byte pin states> CRC

	`04`: Set RGB:
		R,G,B values are 1 byte each.
		Send:		0x04 R G B CRC
		Expect:		0x55 0x4 R G B CRC

	`05`: Get temperature:
		Send:		0x05 CRC
		Expect:		Not implemented

	`06`: Set motor threshold value:
		Send:		0x6 <1 byte, new value> CRC
		Expect:		0x55 0x6 <new value> CRC

### Events

	`03`: If input event occurs 0x3 <1 byte, pin no> CRC is sent by mcu.


SAMPLE MESSAGES:
------
	all messages in hex format

	Send 		0202
	expect 		05 <pin states> CRC

	clear all pins
	Send 		01000001
	expect		5501000054

	set all pins
	Send 		01FFFF01
	expect		5501FFFF54

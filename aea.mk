DEPS_DB := $(CURDIR)/dependencies.txt

PRE_MAKE_ALL_RULE_HOOK:
	@cd ${CHIBIOS} && $(eval COMMIT=$(shell git rev-parse HEAD)) echo "ChibiOS $(COMMIT)" > $(DEPS_DB)

POST_MAKE_ALL_RULE_HOOK:

CLEAN_RULE_HOOK:
	@echo "Cleanup hook..."
	@echo
	@find $(CURDIR) -iname '*.gch' -exec rm {} \;
	@rm $(CURDIR)/_breakpoints.txt 2> /dev/null || true
	@rm $(CURDIR)/core 2> /dev/null || true

include ./mcu-debug/main.mk

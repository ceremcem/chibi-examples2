DEPS_DB := $(CURDIR)/dependencies.txt

CHIBIOS_BRANCH := $(shell cd ${CHIBIOS} && git branch | grep \* | cut -d ' ' -f2)
CHIBIOS_COMMIT := $(shell cd ${CHIBIOS} && git rev-parse HEAD)

PRE_MAKE_ALL_RULE_HOOK:
	@echo "ChibiOS/$(CHIBIOS_BRANCH) $(CHIBIOS_COMMIT)" > $(DEPS_DB)

POST_MAKE_ALL_RULE_HOOK:

CLEAN_RULE_HOOK:
	@echo "Cleanup hook..."
	@echo
	@find $(CURDIR) -iname '*.gch' -exec rm {} \;
	@rm $(CURDIR)/_breakpoints.txt 2> /dev/null || true
	@rm $(CURDIR)/core 2> /dev/null || true

include ./mcu-debug/main.mk

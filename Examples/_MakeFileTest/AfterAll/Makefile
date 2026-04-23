
RULES := rule0

include Makefile0.mk # RULES += rule1

test0: $(RULES) # only rule0 and rule1
	@$(MAKE) -s $(RULES) # all rules
	@echo $(RULES) # all rules

RULES += rule2

include Makefile1.mk # RULES += rule3

test1: $(RULES) # all rules
	@$(MAKE) -s $(RULES) # all rules
	@echo $(RULES) # all rules



rule0:
	@echo 0

rule1:
	@echo 1

rule2:
	@echo 2

rule3:
	@echo 3

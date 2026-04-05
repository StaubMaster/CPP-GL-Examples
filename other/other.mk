
ifndef OTHER_DIR
$(error OTHER_DIR not set)
endif

################################################################
#                             OTHER                            #
################################################################

OTHER_LIST =

################################################################

other_all:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach other, $(OTHER_LIST), \
		$(MAKE) -C $(other) -s all ; \
	)

other_clean:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach other, $(other_LIST), \
		if [ -d $(other) ] ; OTHER_LIST \
			$(MAKE) -C $(other) -s clean ; \
		fi ; \
	)

other_fclean:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach other, $(OTHER_LIST), \
		if [ -d $(other) ] ; then \
			$(MAKE) -C $(other) -s fclean ; \
		fi ; \
	)

.PHONY: other_all other_clean other_fclean

################################################################

include $(OTHER_DIR)/UserInterface.mk
#include $(OTHER_DIR)/InterPolation.mk

################################################################

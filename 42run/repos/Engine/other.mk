
################################################################
#                             OTHER                            #
################################################################

OTHER_DIR_LIST := $(dir $(OTHER_LIST))

################################################################

other_all:
ifdef OTHER_DIR_LIST
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach other, $(OTHER_DIR_LIST), \
		if [ -d $(other) ] ; then \
			$(MAKE) -C $(other) -s all ; \
		fi ; \
	)
endif

other_clean:
ifndef OTHER_DIR_LIST
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach other, $(OTHER_DIR_LIST), \
		if [ -d $(other) ] ; then \
			$(MAKE) -C $(other) -s clean ; \
		fi ; \
	)
endif

other_fclean:
ifdef OTHER_DIR_LIST
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach other, $(OTHER_DIR_LIST), \
		if [ -d $(other) ] ; then \
			$(MAKE) -C $(other) -s fclean ; \
		fi ; \
	)
endif

.PHONY: other_all other_clean other_fclean

################################################################

$(OTHER_LIST):
	@$(MAKE) -C $(dir $@) -s

################################################################

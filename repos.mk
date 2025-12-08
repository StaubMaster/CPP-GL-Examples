
ifndef REPOS_DIR
$(error REPOS_DIR needs to be set. REPOS_DIR := other/)
endif



################################################################
#                             REPO                             #
################################################################

REPOS_STATIC = 
REPOS_DYNAMIC = 
REPOS_ALL = $(REPOS_STATIC) $(REPOS_DYNAMIC)

################################################################

repos: repos_clone
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach repo, $(REPOS_ALL), \
		$(MAKE) -C $(repo) -s ; \
	)

repos_all: repos_clone
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach repo, $(REPOS_ALL), \
		$(MAKE) -C $(repo) -s all ; \
	)

repos_clean:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach repo, $(REPOS_ALL), \
		if [ -d $(repo) ] ; then \
			$(MAKE) -C $(repo) -s clean ; \
		fi ; \
	)

repos_fclean:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach repo, $(REPOS_ALL), \
		if [ -d $(repo) ] ; then \
			$(MAKE) -C $(repo) -s fclean ; \
		fi ; \
	)

.PHONY: repos repos_all repos_clean repos_fclean

################################################################

repos_clone:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	mkdir -p $(REPOS_DIR)
	$(MAKE) $(REPOS_DYNAMIC) -s

repos_rm:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@rm -rf $(REPOS_DYNAMIC)
	@rm -rf $(REPOS_DIR)

.PHONY: repos_clone repos_rm

################################################################

#repos_librarys:
#	@echo $(foreach repo,\
		$(REPOS),\
		$(foreach library,\
			$(shell $(MAKE) -C $(repo) -s librarys),\
			$(repo)/$(library)\
		)\
	)

#repos_includes:
#	@echo $(foreach repo,\
		$(REPOS),\
		$(foreach include,\
			$(shell $(MAKE) -C $(repo) -s includes),\
			$(repo)/$(include)\
		)\
	)

#repos_arguments:
#	@echo $(foreach repo,\
		$(REPOS),\
		$(foreach argument,\
			$(shell $(MAKE) -C $(repo) -s arguments),\
			$(repo)/$(argument)\
		)\
	)

#.PHONY: repos_librarys repos_includes repos_arguments

################################################################





################################################################

define repoLibrarys
	$(foreach library,$(shell if [ -d $(1) ]; then $(MAKE) -C $(1) -s librarys; fi),$(1)/$(library))
endef

define repoIncludes
	$(foreach include,$(shell if [ -d $(1) ]; then $(MAKE) -C $(1) -s includes; fi),$(1)/$(include))
endef

define repoArguments
	$(foreach argument,$(shell if [ -d $(1) ]; then $(MAKE) -C $(1) -s arguments; fi),$(argument))
endef

################################################################

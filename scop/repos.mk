
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
	@$(MAKE) $(REPOS_DYNAMIC) -s

repos_rm:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@rm -rf $(REPOS_DYNAMIC)

.PHONY: repos_clone repos_rm

################################################################


ifndef REPOS_DIR
$(error REPOS_DIR needs to be set. REPOS_DIR := other/)
endif



################################################################
#                             REPO                             #
################################################################

REPOS_LIST =

################################################################

repos_all:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach repo, $(REPOS_LIST), \
		$(MAKE) -C $(repo) -s all ; \
	)

repos_clean:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach repo, $(REPOS_LIST), \
		if [ -d $(repo) ] ; then \
			$(MAKE) -C $(repo) -s clean ; \
		fi ; \
	)

repos_fclean:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(foreach repo, $(REPOS_LIST), \
		if [ -d $(repo) ] ; then \
			$(MAKE) -C $(repo) -s fclean ; \
		fi ; \
	)

.PHONY: repos_all repos_clean repos_fclean

################################################################

repos_clone:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	git submodule --quiet update --init

repos_rm:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
#	git submodule --quiet deinit --all
#	when cloning, the submodules are empty, so the stuff in repos_clone needs to be done to pull them
#	repos_rm is supposed to change them back to being empty, but git dosent like that ?
#	not sure how to do that

.PHONY: repos_clone repos_rm

################################################################

include $(REPOS_DIR)/Engine.mk
include $(REPOS_DIR)/FileManager.mk
include $(REPOS_DIR)/OpenGL.mk

################################################################

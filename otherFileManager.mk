
################################################################
#                          FileManager                         #
################################################################

FM_HTTPS := https://github.com/StaubMaster/CPP-GL-FileManager.git
FM_REPO := $(REPOS_DIR)/FileManager

REPOS_DYNAMIC += $(FM_REPO)

#FM_LIBRARYS = $(call repoLibrarys,$(FM_REPO))
#FM_INCLUDES = $(call repoIncludes,$(FM_REPO))
#FM_ARGUMENTS = $(call repoArguments,$(FM_REPO))

FM_LIBRARYS = $(FM_REPO)/FileManager.a
FM_INCLUDES = $(FM_REPO)/include

LIBRARYS += $(FM_LIBRARYS)
INCLUDES += $(FM_INCLUDES)
ARGUMENTS += $(FM_ARGUMENTS)

$(FM_REPO) :
	git clone $(FM_HTTPS) $(FM_REPO) -q
	$(MAKE) -C $(FM_REPO) repos_clone -s

$(FM_LIBRARYS) : $(FM_REPO)
	$(MAKE) -C $(FM_REPO) $(@:$(FM_REPO)/%=%) -s

################################################################

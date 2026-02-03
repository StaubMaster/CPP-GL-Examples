
################################################################
#                          FileManager                         #
################################################################

FM_URL := https://github.com/StaubMaster/CPP-FileManager.git
FM_DIR := $(REPOS_DIR)/FileManager

REPOS_DYNAMIC += $(FM_DIR)

#FM_LIBRARYS = $(call repoLibrarys,$(FM_DIR))
#FM_INCLUDES = $(call repoIncludes,$(FM_DIR))
#FM_ARGUMENTS = $(call repoArguments,$(FM_DIR))

FM_LIBRARYS = $(FM_DIR)/FileManager.a
FM_INCLUDES = $(FM_DIR)/include

LIBRARYS += $(FM_LIBRARYS)
INCLUDES += $(FM_INCLUDES)
ARGUMENTS += $(FM_ARGUMENTS)

$(FM_DIR) :
	git clone $(FM_URL) -q $(FM_DIR)

$(FM_LIBRARYS) : $(FM_DIR)
	$(MAKE) -C $(FM_DIR) -s $(@:$(FM_DIR)/%=%)

################################################################

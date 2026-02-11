
################################################################
#                            Engine                            #
################################################################

ENGINE_DIR := $(REPOS_DIR)/Engine

REPOS_LIST += $(ENGINE_DIR)

#ENGINE_LIBRARYS = $(call repoLibrarys,$(ENGINE_DIR))
#ENGINE_INCLUDES = $(call repoIncludes,$(ENGINE_DIR))
#ENGINE_ARGUMENTS = $(call repoArguments,$(ENGINE_DIR))

ENGINE_LIBRARYS = $(ENGINE_DIR)/Engine.a
ENGINE_INCLUDES = $(ENGINE_DIR)/include

LIBRARYS += $(ENGINE_LIBRARYS)
INCLUDES += $(ENGINE_INCLUDES)
ARGUMENTS += $(ENGINE_ARGUMENTS)

$(ENGINE_LIBRARYS) : $(ENGINE_DIR)
	$(MAKE) -C $(ENGINE_DIR) -s $(@:$(ENGINE_DIR)/%=%)

################################################################

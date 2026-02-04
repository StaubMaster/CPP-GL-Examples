
################################################################
#                            Engine                            #
################################################################

ENGINE_URL := https://github.com/StaubMaster/CPP-GL-Engine.git
ENGINE_DIR := $(REPOS_DIR)/Engine

REPOS_DYNAMIC += $(ENGINE_DIR)

ENGINE_LIBRARYS = $(ENGINE_DIR)/Engine.a
ENGINE_INCLUDES = $(ENGINE_DIR)/include

LIBRARYS += $(ENGINE_LIBRARYS)
INCLUDES += $(ENGINE_INCLUDES)
ARGUMENTS += $(ENGINE_ARGUMENTS)

$(ENGINE_DIR) :
	git clone $(ENGINE_URL) -q $(ENGINE_DIR)

$(ENGINE_LIBRARYS) : $(ENGINE_DIR)
	$(MAKE) -C $(ENGINE_DIR) -s $(@:$(ENGINE_DIR)/%=%)

################################################################


################################################################
#                            Engine                            #
################################################################

ENGINE_DIR := $(REPOS_DIR)/Engine

REPOS_LIST += $(ENGINE_DIR)

ENGINE_LIBRARYS = $(ENGINE_DIR)/Engine.a $(ENGINE_DIR)/ValueType/ValueType.a $(ENGINE_DIR)/Generics/Generics.a $(ENGINE_DIR)/Graphics/Graphics.a
ENGINE_INCLUDES = $(ENGINE_DIR)/include  $(ENGINE_DIR)/ValueType/include     $(ENGINE_DIR)/Generics/include    $(ENGINE_DIR)/Graphics/include

LIBRARYS += $(ENGINE_LIBRARYS)
INCLUDES += $(ENGINE_INCLUDES)
ARGUMENTS += $(ENGINE_ARGUMENTS)

$(ENGINE_LIBRARYS) : $(ENGINE_DIR)
	$(MAKE) -C $(ENGINE_DIR) -s $(@:$(ENGINE_DIR)/%=%)

################################################################

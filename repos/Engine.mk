
################################################################
#                            Engine                            #
################################################################

ENGINE_DIR := $(REPOS_DIR)/Engine

REPOS_LIST += $(ENGINE_DIR)

ENGINE_LIBRARYS  := $(ENGINE_DIR)/Engine.a $(ENGINE_DIR)/ValueType/ValueType.a $(ENGINE_DIR)/Generics/Generics.a $(ENGINE_DIR)/FileManager/FileManager.a $(ENGINE_DIR)/OpenGL/OpenGL.a $(ENGINE_DIR)/Display/Display.a $(ENGINE_DIR)/Graphics/Graphics.a $(ENGINE_DIR)/User/User.a
ENGINE_INCLUDES  := $(ENGINE_DIR)/include  $(ENGINE_DIR)/ValueType/include     $(ENGINE_DIR)/Generics/include    $(ENGINE_DIR)/FileManager/include       $(ENGINE_DIR)/OpenGL/include  $(ENGINE_DIR)/Display/include   $(ENGINE_DIR)/Graphics/include    $(ENGINE_DIR)/User/include

ifeq ($(CheckOS), Windows)
ENGINE_ARGUMENTS := -lglfw3 -lgdi32
endif

ifeq ($(CheckOS), Darwin)
ENGINE_ARGUMENTS := -lglfw
endif

ifeq ($(CheckOS), Linux)
ENGINE_ARGUMENTS := -lglfw
endif

LIBRARYS  += $(ENGINE_LIBRARYS)
INCLUDES  += $(ENGINE_INCLUDES)
ARGUMENTS += $(ENGINE_ARGUMENTS)

$(ENGINE_LIBRARYS) : $(ENGINE_DIR)
	@$(MAKE) -C $(ENGINE_DIR) -s $(@:$(ENGINE_DIR)/%=%)

################################################################

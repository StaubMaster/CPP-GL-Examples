
################################################################
#                            Engine                            #
################################################################

ENGINE_DIR := $(REPOS_DIR)/Engine

REPOS_LIST += $(ENGINE_DIR)

ENGINE_LIBRARYS  := Debug/Debug.a ValueType/ValueType.a Generics/Generics.a FileManager/FileManager.a PolyHedra/PolyHedra.a OpenGL/OpenGL.a Display/Display.a Graphics/Graphics.a User/User.a
ENGINE_INCLUDES  := Debug/include ValueType/include     Generics/include    FileManager/include       PolyHedra/include     OpenGL/include  Display/include   Graphics/include    User/include

ifeq ($(CheckOS), Windows)
ENGINE_ARGUMENTS := -lglfw3 -lgdi32
endif

ifeq ($(CheckOS), Darwin)
ENGINE_ARGUMENTS := -lglfw
endif

ifeq ($(CheckOS), Linux)
ENGINE_ARGUMENTS := -lglfw
endif

LIBRARYS  += $(addprefix $(ENGINE_DIR)/,$(ENGINE_LIBRARYS))
INCLUDES  += $(addprefix $(ENGINE_DIR)/,$(ENGINE_INCLUDES))
ARGUMENTS += $(ENGINE_ARGUMENTS)

################################################################

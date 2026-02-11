
################################################################
#                            OpenGL                            #
################################################################

OPENGL_DIR := $(REPOS_DIR)/OpenGL

REPOS_LIST += $(OPENGL_DIR)

#OPENGL_LIBRARYS = $(call repoLibrarys,$(OPENGL_DIR))
#OPENGL_INCLUDES = $(call repoIncludes,$(OPENGL_DIR))
#OPENGL_ARGUMENTS = $(call repoArguments,$(OPENGL_DIR))

OPENGL_LIBRARYS = $(OPENGL_DIR)/OpenGL.a
OPENGL_INCLUDES = $(OPENGL_DIR)/include/

ifeq ($(CheckOS), Windows)
OPENGL_ARGUMENTS = -lglfw3 -lgdi32
endif

ifeq ($(CheckOS), Darwin)
OPENGL_ARGUMENTS = -lglfw
endif

ifeq ($(CheckOS), Linux)
OPENGL_ARGUMENTS = -lglfw
endif

LIBRARYS += $(OPENGL_LIBRARYS)
INCLUDES += $(OPENGL_INCLUDES)
ARGUMENTS += $(OPENGL_ARGUMENTS)

$(OPENGL_LIBRARYS) : $(OPENGL_DIR)
	$(MAKE) -C $(OPENGL_DIR) $(@:$(OPENGL_DIR)/%=%) -s

################################################################

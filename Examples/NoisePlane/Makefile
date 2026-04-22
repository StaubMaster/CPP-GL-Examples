
NAME := NoisePlane.a

#COMPILER := c++ -std=c++11
COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror
ARCHIVER := ar -rcs
REMOVER := rm -f

################################################################

BASE_DIR := ../../
include $(BASE_DIR)fancy.mk
FANCY_NAME := NoisePlane

################################################################

FILES_SRC := \
	Plane/Plane.cpp \
	Plane/PlaneValue.cpp \
	Plane/PlaneNeighbours.cpp \
	Plane/PlaneGraphics.cpp \
	Plane/PlaneManager.cpp \
\
	Voxel/Graphics/Voxel.cpp \
	Voxel/Graphics/Main/Data.cpp \
	Voxel/Graphics/Main/Buffer.cpp \
	Voxel/Graphics/Inst/Data.cpp \
	Voxel/Graphics/Inst/Buffer.cpp \
	Voxel/Graphics/Buffer.cpp \
	Voxel/Graphics/Shader.cpp \
	\
	Voxel/Voxel.cpp \
	Voxel/VoxelTemplate.cpp \
	Voxel/VoxelOrientation.cpp \
	Voxel/VoxelEnums.cpp \
	Voxel/Chunk.cpp \
	Voxel/ChunkNeighbours.cpp \
	Voxel/ChunkManager.cpp \
\
	Menus/Main.cpp \
	Menus/Options.cpp \
\
	main.cpp \

FILES_OBJ := $(FILES_SRC:.cpp=.o)

################################################################

all:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s $(FILES_OBJ)
	@$(MAKE) -s $(NAME)

clean:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(REMOVER) $(FILES_OBJ)

fclean:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s clean
	@$(REMOVER) $(NAME)

re:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s fclean
	@$(MAKE) -s all

exe:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s $(FILES_OBJ)
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$(NAME))
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(FILES_OBJ) -o $(NAME) $(LIBRARYS) $(ARGUMENTS)

.PHONY: all clean fclean re exe

$(NAME) : $(FILES_OBJ) $(LIBRARYS)
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@$(ARCHIVER) $(NAME) $(FILES_OBJ)
#	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(FILES_OBJ) -o $@ $(LIBRARYS) $(ARGUMENTS)

################################################################

%.o : %.cpp
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ -c $<

################################################################

LIBRARYS = 
INCLUDES = ./ ../ $(OUTSIDE_DIR)/_include
ARGUMENTS = 

ARGS_LIBRARYS = $(foreach library, $(LIBRARYS),$(library))
ARGS_INCLUDES = $(foreach include, $(INCLUDES),-I$(include))

################################################################

OTHER_DIR := $(BASE_DIR)/other/
include $(OTHER_DIR)/other.mk

REPOS_DIR := $(BASE_DIR)/repos/
include $(REPOS_DIR)/repos.mk

################################################################

include $(OTHER_DIR)/UserInterface.mk

include $(REPOS_DIR)/Engine.mk
include $(REPOS_DIR)/FileManager.mk
include $(REPOS_DIR)/OpenGL.mk

################################################################

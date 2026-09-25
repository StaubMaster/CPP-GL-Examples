
#COMPILER := c++ -std=c++11
COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror


################################################################

BASE_DIR := ../
include $(BASE_DIR)fancy.mk
FANCY_NAME := Test

################################################################

NAME := test.exe

FILES_SRC := \
	TransformationScaling.cpp
#	EulerMatrixStuff.cpp
#	Container.cpp
#	EntryContainer.cpp
#	Angle3D.cpp
#	CopyConstruct.cpp
#	Graphics.cpp
#	Undex.cpp
#	$(DIR_SRC)/Debug.cpp \
#	../src/Miscellaneous/Container/Behaviour.cpp

FILES_OBJ := $(FILES_SRC:.cpp=.o)

################################################################

all:
	$(MAKE) -C $(BASE_DIR) -s
#	$(COMPILER) $(FLAGS) $(INCLUDES) -o $(NAME) $(FILES)
	$(COMPILER) $(FLAGS) $(INCLUDES) -o $(NAME) $(FILES_SRC) $(LIBRARYS) $(ARGUMENTS)

fclean:
	rm -f $(NAME)

.PHONY: all fclean

################################################################

#LIBRARYS := ..//Engine.a ..//other//OpenGL/openGL.a ..//other//FileManager/FileManager.a
#INCLUDES := -I..//include/ -I..//other//OpenGL/../ -I..//other//FileManager/include

LIBRARYS := $(BASE_DIR)/Engine.a
INCLUDES := -I$(BASE_DIR)/include/
ARGUMENTS :=

ifeq ($(CheckOS), Windows)
ARGUMENTS := -lglfw3 -lgdi32
endif

ifeq ($(CheckOS), Darwin)
ARGUMENTS := -lglfw
endif

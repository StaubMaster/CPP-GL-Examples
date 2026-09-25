
#COMPILER := c++ -std=c++11
COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror

################################################################

BASE_DIR := ../../
include $(BASE_DIR)fancy.mk
FANCY_NAME := ContainerTest

################################################################

NAME := Test.exe

FILES_SRC := \
	main.cpp

FILES_OBJ := $(FILES_SRC:.cpp=.o)

################################################################

all:
#	$(MAKE) -C $(BASE_DIR) -s
#	$(COMPILER) $(FLAGS) $(INCLUDES) -o $(NAME) $(FILES)
	$(COMPILER) $(FLAGS) $(INCLUDES) -o $(NAME) $(FILES_SRC) $(LIBRARYS) $(ARGUMENTS)

fclean:
	rm -f $(NAME)

.PHONY: all fclean

################################################################

LIBRARYS :=
INCLUDES := -I$(BASE_DIR)/include/
ARGUMENTS :=

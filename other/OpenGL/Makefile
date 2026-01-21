
NAME := openGL.a
FLAGS := -Wall -Wextra -Werror



FILES_SRC := \
	openGL.cpp \
	glad/glad.c

FILES_OBJ := $(FILES_SRC)
FILES_OBJ := $(FILES_OBJ:.c=.o)
FILES_OBJ := $(FILES_OBJ:.cpp=.o)





################################################################
#                           OS Stuff                           #
################################################################

ifeq ($(OS), Windows_NT)
	CheckOS := Windows
else
	CheckOS := $(shell uname -s)
endif

################################################################





################################################################

all:
	$(MAKE) $(FILES_OBJ)
	$(MAKE) $(NAME)

clean:
	rm -f $(FILES_OBJ)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re

$(NAME) : $(FILES_OBJ)
	ar -rcs $(NAME) $(FILES_OBJ)

################################################################





%.o : %.c
	cc $(FLAGS) -c $^ -o $@

%.o : %.cpp
	c++ -std=c++11 $(FLAGS) -c $^ -o $@







################################################################

LIBRARYS = $(NAME)
INCLUDES = ../
ARGUMENTS = $(OS_ARGS)

librarys:
	@echo $(LIBRARYS)

includes:
	@echo $(INCLUDES)

arguments:
	@echo $(ARGUMENTS)

.PHONY: librarys includes arguments

################################################################



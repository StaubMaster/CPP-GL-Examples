
NAME := openGL.a

COMPILER_C := cc -fPIE
COMPILER_CPP := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror
ARCHIVER := ar -rcs
REMOVER := rm -f

FANCY_NAME := OpenGL
include fancy.mk



FILES_SRC := \
	openGL.cpp \
	glad/glad.c

FILES_OBJ := $(FILES_SRC)
FILES_OBJ := $(FILES_OBJ:.c=.o)
FILES_OBJ := $(FILES_OBJ:.cpp=.o)



################################################################

all:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s $(NAME)

clean:
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(FILES_OBJ)

fclean:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s clean
	@$(REMOVER) $(NAME)

re:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY: all clean fclean re

$(NAME) : $(FILES_OBJ)
	@$(call fancyNameArchivingEcho,$@)
	@$(ARCHIVER) $(NAME) $(FILES_OBJ)

################################################################





%.o : %.c
	@$(call fancyNameCompilingEcho,$@)
	@$(COMPILER_C) $(FLAGS) -c $^ -o $@

%.o : %.cpp
	@$(call fancyNameCompilingEcho,$@)
	@$(COMPILER_CPP) $(FLAGS) -c $^ -o $@







################################################################
#                           OS Stuff                           #
################################################################
#
#ifeq ($(OS), Windows_NT)
#	CheckOS := Windows
#else
#	CheckOS := $(shell uname -s)
#endif
#
################################################################
#
#LIBRARYS := $(NAME)
#INCLUDES := ../
#ARGUMENTS := $(OS_ARGS)
#
#librarys:
#	@echo $(LIBRARYS)
#
#includes:
#	@echo $(INCLUDES)
#
#arguments:
#	@echo $(ARGUMENTS)
#
#.PHONY: librarys includes arguments
#
################################################################

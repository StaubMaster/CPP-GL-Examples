
NAME := openGL.a

COMPILER_C := cc -fPIE
COMPILER_CPP := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror
ARCHIVER := ar -rcs
REMOVER := rm -f

FANCY_NAME := OpenGL
include fancy.mk



DIR_SRC := src/
DIR_OBJ := obj/



FILES_SRC := \
	$(DIR_SRC)OpenGLEnums.cpp \
	$(DIR_SRC)OpenGL.cpp \
	glad/glad.c

FILES_OBJ := $(FILES_SRC:$(DIR_SRC)%=$(DIR_OBJ)%)
FILES_OBJ := $(FILES_OBJ:.c=.o)
FILES_OBJ := $(FILES_OBJ:.cpp=.o)



################################################################

all:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s $(FILES_OBJ)
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

test:
	$(COMPILER_CPP) $(FLAGS) EnumBits.cpp -o EnumBits.exe

################################################################





$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@$(call fancyNameCompilingEcho,$@)
	@mkdir -p $(dir $@)
	@$(COMPILER_C) $(FLAGS) $(ARGS_INCLUDES) -c $^ -o $@

$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp
	@$(call fancyNameCompilingEcho,$@)
	@mkdir -p $(dir $@)
	@$(COMPILER_CPP) $(FLAGS) $(ARGS_INCLUDES) -c $^ -o $@





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

LIBRARYS := $(NAME)
INCLUDES := include
ARGUMENTS := $(OS_ARGS)

ARGS_LIBRARYS = $(foreach library,$(LIBRARYS),$(library))
ARGS_INCLUDES = $(foreach include, $(INCLUDES),-I$(include))

librarys:
	@echo $(LIBRARYS)

includes:
	@echo $(INCLUDES)

arguments:
	@echo $(ARGUMENTS)

.PHONY: librarys includes arguments

################################################################

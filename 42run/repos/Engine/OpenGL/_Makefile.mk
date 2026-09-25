
NAME := OpenGL.a
COMPILER_C := cc -fPIE
COMPILER_CPP := g++ -std=c++11
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
	@$(MAKE) -s $(NAME)
	@$(COMPILER_CPP) $(FLAGS) $(ARGS_INCLUDES) main.cpp -o test.exe $(LIBRARYS) $(ARGUMENTS)

decap:
	@$(COMPILER_CPP) $(FLAGS) _MacroDecapitator.cpp -o MacroDecapitator.exe

.PHONY: test decap

################################################################





#this is just for glad.c
#since having the directorys here makes it unrecognized
%.o : %.c
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

ifeq ($(CheckOS), Windows)
ARGUMENTS = -lglfw3 -lgdi32
endif

ifeq ($(CheckOS), Darwin)
ARGUMENTS = -lglfw
endif

ifeq ($(CheckOS), Linux)
ARGUMENTS = -lglfw
endif

ARGS_INCLUDES = $(foreach include, $(INCLUDES),-I$(include))

librarys:
	@echo $(LIBRARYS)

includes:
	@echo $(INCLUDES)

arguments:
	@echo $(ARGUMENTS)

.PHONY: librarys includes arguments

################################################################


#COMPILER := c++ -std=c++11 # normal
COMPILER := g++ -g -std=c++11 # debug
FLAGS := -Wall -Wextra -Werror
ARCHIVER := ar -rcs
REMOVER := rm -f

################################################################

NAME := TestLibrary.a
FANCY_NAME := TestLibrary

################################################################

include ../../../fancy.mk

################################################################

DIR_SRC := .
DIR_OBJ := .

FILES := code.cpp

FILES_SRC := $(addprefix $(DIR_SRC)/,$(FILES))
FILES_OBJ := $(addprefix $(DIR_OBJ)/,$(FILES:.cpp=.o))

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

.PHONY: all clean fclean

$(NAME) : $(FILES_OBJ)
	@$(call fancyNameCompilingEcho,$@)
	@$(ARCHIVER) $(NAME) $(FILES_OBJ)

################################################################

%.o : %.cpp
	@$(call fancyNameCompilingEcho,$@)
	@$(COMPILER) $(FLAGS) -o $@ -c $<

################################################################

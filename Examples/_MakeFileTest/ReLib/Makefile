
#COMPILER := c++ -std=c++11 # normal
COMPILER := g++ -g -std=c++11 # debug
FLAGS := -Wall -Wextra -Werror
ARCHIVER := ar -rcs
REMOVER := rm -f

################################################################

NAME := test.exe
FANCY_NAME := test

################################################################

include ../../fancy.mk

################################################################

DIR_SRC := .
DIR_OBJ := .

FILES := main.cpp

FILES_SRC := $(addprefix $(DIR_SRC)/,$(FILES))
FILES_OBJ := $(addprefix $(DIR_OBJ)/,$(FILES:.cpp=.o))

################################################################

include Library.mk

################################################################

all:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s other_all
	@$(MAKE) -s $(FILES_OBJ)
	@$(MAKE) -s $(NAME)

clean:
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(FILES_OBJ)

fclean:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s clean
	@$(REMOVER) $(NAME)
	@$(MAKE) -s other_fclean

.PHONY: all clean fclean

$(NAME) : $(FILES_OBJ) $(LIBRARYS)
	@$(call fancyNameCompilingEcho,$@)
	@$(COMPILER) $(FLAGS) -o $(NAME) $(FILES_OBJ) $(LIBRARYS)

################################################################

%.o : %.cpp
	@$(call fancyNameCompilingEcho,$@)
	@$(COMPILER) $(FLAGS) -o $@ -c $<

################################################################

OTHER_DIR := ../../other/
include $(OTHER_DIR)/other.mk

################################################################

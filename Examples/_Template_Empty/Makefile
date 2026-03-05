
NAME := ImageTest.exe

#COMPILER := c++ -std=c++11
COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror
REMOVER := rm -f

################################################################

BASE_DIR := ../../
include $(BASE_DIR)fancy.mk
FANCY_NAME := ImageTest

################################################################

FILES_SRC := \
	BitMap.cpp \
	main.cpp
FILES_OBJ := $(FILES_SRC:.cpp=.o)

################################################################

all:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s repos_all
	@$(MAKE) -s other_all
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

.PHONY: all clean fclean re

$(NAME) : $(FILES_OBJ) $(LIBRARYS)
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@mkdir -p logs/
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(FILES_OBJ) -o $@ $(LIBRARYS) $(ARGUMENTS)

################################################################

%.o : %.cpp
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ -c $<

################################################################

LIBRARYS = 
INCLUDES = .
ARGUMENTS = 

ARGS_LIBRARYS = $(foreach library, $(LIBRARYS),$(library))
ARGS_INCLUDES = $(foreach include, $(INCLUDES),-I$(include))

################################################################

OTHER_DIR := $(BASE_DIR)/other/
include $(OTHER_DIR)/other.mk

REPOS_DIR := $(BASE_DIR)/repos/
include $(REPOS_DIR)/repos.mk

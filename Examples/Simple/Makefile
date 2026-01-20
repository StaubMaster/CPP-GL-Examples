
#COMPILER := c++ -std=c++11
COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror
#FLAGS += -fsanitize=address,undefined
#	gdb prog.exe

BASE_DIR := ../../



MAINS = \
	Basic.cpp \
	Light.cpp

EXES = $(MAINS:.cpp=.exe)

FILES_OBJ := $(FILES_SRC:.cpp=.o)



################################################################
#                  Standard Makefile Commands                  #
################################################################

all:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s repos_clone
	@$(MAKE) -s $(EXES)

clean:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)

fclean:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s clean
	@rm -f $(EXES)

re:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY: all clean fclean re

################################################################



include $(BASE_DIR)fancy.mk
FANCY_NAME := Simple



%.exe : %.cpp
	@$(MAKE) $(LIBRARYS)
	@mkdir -p logs/
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@echo $(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ $< $(ARGS_LIBRARYS) $(ARGUMENTS)
	$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ $< $(ARGS_LIBRARYS) $(ARGUMENTS)



################################################################
#                     Environment Variables                    #
################################################################

LIBRARYS = 
INCLUDES = $(BASE_DIR)src
ARGUMENTS = 

ARGS_LIBRARYS = $(foreach library, $(LIBRARYS),$(library))
ARGS_INCLUDES = $(foreach include, $(INCLUDES),-I$(include))

librarys: repos_clone
	@echo $(LIBRARYS)

includes: repos_clone
	@echo $(INCLUDES)

arguments: repos_clone
	@echo $(ARGUMENTS)

.PHONY: librarys includes arguments

################################################################



REPOS_DIR := $(BASE_DIR)other/
include $(BASE_DIR)repos.mk
include $(BASE_DIR)repo_Engine.mk

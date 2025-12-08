
COMPILER := c++ -std=c++11
FLAGS := -Wall -Wextra -Werror

BASE_DIR := ../../



NAME := InterPolation.exe

FILES_SRC := \
	InterPolation.cpp

FILES_OBJ := $(FILES_SRC:.cpp=.o)



################################################################
#                  Standard Makefile Commands                  #
################################################################

all:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s repos_clone
	@$(MAKE) -s $(FILES_OBJ)
	@$(MAKE) -s $(NAME)

clean:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@rm -f $(FILES_OBJ)

fclean:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s clean
	@rm -f $(NAME)

re:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY: all clean fclean re

$(NAME) : $(FILES_OBJ)
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	$(MAKE) $(ENGINE_LIBRARYS)
	@mkdir -p logs/
	$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(FILES_OBJ) -o $@ $(LIBRARYS) $(ARGUMENTS)

################################################################



include $(BASE_DIR)fancy.mk
FANCY_NAME := InterPolation



%.o : %.cpp
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ -c $<



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

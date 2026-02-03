
NAME := scop
COMPILER := c++ -std=c++11
#COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror

include $(BASE_DIR)fancy.mk
FANCY_NAME := scop



FILES_SRC = main.cpp

FILES_OBJ = $(FILES_SRC:.cpp=.o)





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
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) $(LIBRARYS)
	@mkdir -p logs/
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(FILES_OBJ) -o $@ $(LIBRARYS) $(ARGUMENTS)

################################################################





%.o : %.cpp
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ -c $<





################################################################
#                     Environment Variables                    #
################################################################

LIBRARYS := 
INCLUDES := 
ARGUMENTS := 

ARGS_INCLUDES = $(foreach include, $(INCLUDES),-I$(include))

################################################################



REPOS_DIR := other/
include repos.mk
include other/Engine.mk
include other/FileManager.mk
include other/OpenGL.mk

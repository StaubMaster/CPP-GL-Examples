

NAME := InterPolation.exe
#COMPILER := c++ -std=c++11
COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror

BASE_DIR := ../../

include $(BASE_DIR)fancy.mk
FANCY_NAME := InterPolation





FILES_SRC := \
	SplineSegment3DControl.cpp \
	main.cpp

FILES_OBJ := $(FILES_SRC:.cpp=.o)



################################################################
#                  Standard Makefile Commands                  #
################################################################

all:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s repos_all
	@$(MAKE) -s $(FILES_OBJ)
	@$(MAKE) -s $(NAME)

clean:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@rm -f $(FILES_OBJ)
	@$(MAKE) -C $(BASE_DIR)/other/UI -s clean
	@$(MAKE) -C $(BASE_DIR)/other/Spline -s clean

fclean:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s clean
	@rm -f $(NAME)
	@$(MAKE) -C $(BASE_DIR)/other/UI -s fclean
	@$(MAKE) -C $(BASE_DIR)/other/Spline -s fclean

re:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY: all clean fclean re

$(NAME) : $(FILES_OBJ) $(LIBRARYS)
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@mkdir -p logs/
	$(MAKE) $(LIBRARYS)
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(FILES_OBJ) -o $@ $(LIBRARYS) $(ARGUMENTS)

################################################################



%.o : %.cpp
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ -c $<



################################################################
#                     Environment Variables                    #
################################################################

LIBRARYS = 
INCLUDES = .
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



$(BASE_DIR)/other/UI/UI.a:
	$(MAKE) -C $(BASE_DIR)/other/UI -s all
LIBRARYS += $(BASE_DIR)/other/UI/UI.a
INCLUDES += $(BASE_DIR)/other

$(BASE_DIR)/other/Spline/Spline.a:
	$(MAKE) -C $(BASE_DIR)/other/Spline -s all
LIBRARYS += $(BASE_DIR)/other/Spline/Spline.a
INCLUDES += $(BASE_DIR)/other



REPOS_DIR := $(BASE_DIR)repos/
include $(REPOS_DIR)/repos.mk

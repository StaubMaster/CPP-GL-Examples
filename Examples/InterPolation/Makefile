

NAME := InterPolation.exe
#COMPILER := c++ -std=c++11
COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror

BASE_DIR := ../../
UI_DIR := $(BASE_DIR)/src/UI/
SPLINE_DIR := $(BASE_DIR)/src/Spline/

include $(BASE_DIR)fancy.mk
FANCY_NAME := InterPolation





FILES_SRC := \
	$(UI_DIR)/Anchor.cpp \
\
	$(UI_DIR)/Control/Base/Data.cpp \
	$(UI_DIR)/Control/Base/Buffer.cpp \
	$(UI_DIR)/Control/Base/Shader.cpp \
	$(UI_DIR)/Control/Base/Manager.cpp \
	$(UI_DIR)/Control/Base/Base.cpp \
\
	$(UI_DIR)/Control/Window.cpp \
	$(UI_DIR)/Control/Form.cpp \
	$(UI_DIR)/Control/GroupBox.cpp \
	$(UI_DIR)/Control/Button.cpp \
	$(UI_DIR)/Control/TextBox.cpp \
	$(UI_DIR)/Control/Slider.cpp \
	$(UI_DIR)/Control/CheckBox.cpp \
\
	$(UI_DIR)/Text/Data.cpp \
	$(UI_DIR)/Text/Buffer.cpp \
	$(UI_DIR)/Text/Shader.cpp \
	$(UI_DIR)/Text/Manager.cpp \
	$(UI_DIR)/Text/Font/Font.cpp \
	$(UI_DIR)/Text/Font/Template.cpp \
	$(UI_DIR)/Text/Font/Parsing.cpp \
\
	$(SPLINE_DIR)/SplineNode3D.cpp \
	$(SPLINE_DIR)/SplineSegment3D.cpp \
	$(SPLINE_DIR)/SplineCurve3D.cpp \
	$(SPLINE_DIR)/SplineObject.cpp \
\
	SplineSegment3DControl.cpp \
	main.cpp

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
	$(MAKE) $(LIBRARYS)
	@mkdir -p logs/
	$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(FILES_OBJ) -o $@ $(LIBRARYS) $(ARGUMENTS)

################################################################



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
include $(BASE_DIR)other/Engine.mk
include $(BASE_DIR)other/FileManager.mk
include $(BASE_DIR)other/OpenGL.mk

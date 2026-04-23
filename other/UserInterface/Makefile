
NAME := UserInterface.a
FANCY_NAME := UserInterface

################################################################

FILES := \
	Anchor1D.cpp \
	Anchor2D.cpp \
\
	Control/Base/Data.cpp \
	Control/Base/Buffer.cpp \
	Control/Base/Shader.cpp \
	Control/Base/Manager.cpp \
	Control/Base/ObjectData.cpp \
	Control/Base/Object.cpp \
	Control/Base/Base.cpp \
\
	Control/Window.cpp \
	Control/Form.cpp \
	Control/GroupBox.cpp \
	Control/Button.cpp \
	Control/TextBox.cpp \
	Control/Slider.cpp \
	Control/CheckBox.cpp \
\
	Text/Data.cpp \
	Text/Buffer.cpp \
	Text/Shader.cpp \
	Text/Manager.cpp \
	Text/ObjectData.cpp \
	Text/Object.cpp \
	Text/Font/Font.cpp \
	Text/Font/Template.cpp \
	Text/Font/Parsing.cpp \

DIR_SRC := .
DIR_OBJ := .

LIBRARYS :=
INCLUDES := .
ARGUMENTS :=

################################################################

allall: all

BASE_DIR := ../../
OTHER_DIR := $(BASE_DIR)/other/
REPOS_DIR := $(BASE_DIR)/repos/
include $(BASE_DIR)fancy.mk

################################################################

include $(REPOS_DIR)/Engine.mk
include $(REPOS_DIR)/FileManager.mk
include $(REPOS_DIR)/OpenGL.mk

################################################################

include $(BASE_DIR)/MakefileArchiver.mk

################################################################



#NAME := UserInterface.a
#
#COMPILER := g++ -g -std=c++11
#FLAGS := -Wall -Wextra -Werror
#ARCHIVER := ar -rcs
#REMOVER := rm -f
#
#
#
#FANCY_NAME := UserInterface
#include ../../fancy.mk
#
#
#
#DIR_SRC := ./
#DIR_OBJ := ./
#
#FILES_SRC := \
#	Anchor1D.cpp \
#	Anchor2D.cpp \
#\
#	Control/Base/Data.cpp \
#	Control/Base/Buffer.cpp \
#	Control/Base/Shader.cpp \
#	Control/Base/Manager.cpp \
#	Control/Base/ObjectData.cpp \
#	Control/Base/Object.cpp \
#	Control/Base/Base.cpp \
#\
#	Control/Window.cpp \
#	Control/Form.cpp \
#	Control/GroupBox.cpp \
#	Control/Button.cpp \
#	Control/TextBox.cpp \
#	Control/Slider.cpp \
#	Control/CheckBox.cpp \
#\
#	Text/Data.cpp \
#	Text/Buffer.cpp \
#	Text/Shader.cpp \
#	Text/Manager.cpp \
#	Text/ObjectData.cpp \
#	Text/Object.cpp \
#	Text/Font/Font.cpp \
#	Text/Font/Template.cpp \
#	Text/Font/Parsing.cpp \
#
#FILES_OBJ := $(FILES_SRC:$(DIR_SRC)%=$(DIR_OBJ)%)
#FILES_OBJ := $(FILES_OBJ:.cpp=.o)
#
#
#
#all:
#	$(call fancyEcho,$(FANCY_NAME),Target,$@)
#	@$(MAKE) -s $(FILES_OBJ)
#	@$(MAKE) -s $(NAME)
#
#clean:
#	$(call fancyEcho,$(FANCY_NAME),Target,$@)
#	@rm -f $(FILES_OBJ)
#
#fclean:
#	$(call fancyEcho,$(FANCY_NAME),Target,$@)
#	@$(MAKE) -s clean
#	@rm -f $(NAME)
#
#re:
#	$(call fancyEcho,$(FANCY_NAME),Target,$@)
#	@$(MAKE) -s fclean
#	@$(MAKE) -s all
#
#.PHONY: all clean fclean re
#
#
#
#$(NAME) : $(FILES_OBJ)
#	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
#	@$(ARCHIVER) $(NAME) $(FILES_OBJ)
#
#$(DIR_OBJ)%.o : $(DIR_SRC)%.cpp
#	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
#	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ -c $<
#
#
#
#LIBRARYS = 
#INCLUDES = .
#ARGUMENTS = 
#
#ARGS_LIBRARYS = $(foreach library, $(LIBRARYS),$(library))
#ARGS_INCLUDES = $(foreach include, $(INCLUDES),-I$(include))
#
#REPOS_DIR := ../../repos/
#include $(REPOS_DIR)/repos.mk
#include $(REPOS_DIR)/Engine.mk
#include $(REPOS_DIR)/FileManager.mk
#include $(REPOS_DIR)/OpenGL.mk
#
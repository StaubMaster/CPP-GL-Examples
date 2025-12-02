


COMPILER = c++ -std=c++11
FLAGS = -Wall -Wextra -Werror

MAINS = \
	Basic.cpp \
	Multi.cpp \
	Light.cpp
#	Spline.cpp
#	OBJ_Parse.cpp
#	ParticleSimulation.cpp

EXES = $(MAINS:.cpp=.exe)

MAINS_DIR = mains/



################################################################
#                  Standard Makefile Commands                  #
################################################################

#	all currently causes a loop

all:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) repos_clone -s
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

#$(EXES) :
#	$(call fancyEcho,$(FANCY_NAME),Target,$@)
#	$(MAKE) $(ENGINE_LIBRARYS)
#	@mkdir -p logs/
#	@$(MAKE) $@ -s

################################################################



include fancy.mk

FANCY_NAME := Examples



#	put individual Examples here
#	all makes all
#	put stuff into seperate Makefiles ?
#	some are just simple singular files
#	some are more complex
#	might split main into template
#	then all the single file ones would also need another file
#	so just treat everything as multiple files for now ?
#	put all in here for now ?

################################################################
# Basic
# Multi
# Light
# Spline
################################################################
UI_NAME := UserInterface.exe
UI_FILES_SRC := \
	mains/UI/DisplayScale.cpp \
	mains/UI/AxisBox.cpp \
	mains/UI/Anchor.cpp \
	mains/UI/Control/Base/Data.cpp \
	mains/UI/Control/Base/Buffer.cpp \
	mains/UI/Control/Base/Manager.cpp \
	mains/UI/Control/Base/Base.cpp \
	mains/UI/Control/Window.cpp \
	mains/UI/Control/Form.cpp \
	mains/UI/Control/Button.cpp \
	mains/UI/Control/Text.cpp \
	mains/UI/Text/Data.cpp \
	mains/UI/Text/Buffer.cpp \
	mains/UserInterface.cpp
UI_FILES_OBJ := $(UI_FILES_SRC:.cpp=.o)
UI_all:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) repos_clone -s
	@$(MAKE) $(UI_FILES_OBJ) -s
	@$(MAKE) $(UI_NAME) -s
UI_clean:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@rm -f $(UI_FILES_OBJ)
UI_fclean:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s UI_clean
	@rm -f $(UI_NAME)
UI_re:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s UI_fclean
	@$(MAKE) -s UI_all
.PHONY: UI_all UI_clean UI_fclean UI_re
$(UI_NAME) : $(UI_FILES_OBJ)
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	$(MAKE) $(ENGINE_LIBRARYS)
	@mkdir -p logs/
	$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(UI_FILES_OBJ) -o $@ $(LIBRARYS) $(ARGUMENTS)
################################################################
#  maybe not
# OBJ_Parser
# Particle Simulator
################################################################





%.exe : $(MAINS_DIR)%.cpp
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@mkdir -p logs/
	$(MAKE) $(ENGINE_LIBRARYS)
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ $< $(ARGS_LIBRARYS) $(ARGUMENTS)

%.o : %.cpp
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ -c $<





################################################################
#                     Environment Variables                    #
################################################################

LIBRARYS = 
INCLUDES = ./mains
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



include repos.mk

include repo_Engine.mk






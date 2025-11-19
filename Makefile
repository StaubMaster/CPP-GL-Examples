


################################################################
#                           OS Stuff                           #
################################################################

ifeq ($(OS), Windows_NT)
	CheckOS := Windows
else
	CheckOS := $(shell uname -s)
endif

FANCY_NAME := Examples

ifeq ($(CheckOS), Windows)

FANCY_ECHO := echo -e
COLOR_REPO := \e[38;2;127;127;127m
COLOR_TYPE := \e[38;2;127;255;127m
COLOR_FILE := \e[38;2;127;127;255m
COLOR_NONE := \e[m

endif

ifeq ($(CheckOS), Darwin)

FANCY_ECHO := echo
COLOR_REPO := \033[38;2;127;127;127m
COLOR_TYPE := \033[38;2;127;255;127m
COLOR_FILE := \033[38;2;127;127;255m
COLOR_NONE := \033[m

endif

################################################################





COMPILER = c++ -std=c++11
FLAGS = -Wall -Wextra -Werror

MAINS = \
	UserInterface.cpp
#	Basic.cpp \
#	Multi.cpp \
#	Light.cpp \
#	Spline.cpp \
#	OBJ_Parse.cpp
#	ParticleSimulation.cpp

EXES = $(MAINS:.cpp=.exe)

MAINS_DIR = mains/



TARGET_NAMES := 



TARGET_NAMES += UI
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
	mains/UserInterface.cpp
UI_FILES_OBJ := $(UI_FILES_SRC:.cpp=.o)
UI:
	@mkdir -p logs/
	@$(MAKE) -s $(UI_FILES_OBJ)
	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Compiling: $(COLOR_FILE)$(UI_NAME)$(COLOR_NONE)"
	$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(UI_FILES_OBJ) -o $(UI_NAME) $(ARGS_LIBRARYS) $(ARGUMENTS)

UI_clean:
	rm -f $(UI_FILES_OBJ)

.PHONY: UI

%.o : %.cpp
	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Compiling: $(COLOR_FILE)$@$(COLOR_NONE)"
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ -c $<

test:
	@$(MAKE) $(TARGET_NAMES)
test_clean:
	$(MAKE) $(TARGET_NAMES)_clean




################################################################
#                  Standard Makefile Commands                  #
################################################################

all: repos
	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
	@$(MAKE) -s $(EXES)

clean:
	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"

fclean:
	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
	@$(MAKE) -s clean
	@rm -f $(EXES)

re:
	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Target: $(COLOR_FILE)$@$(COLOR_NONE)"
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY: all clean fclean re

################################################################





%.exe : $(MAINS_DIR)%.cpp repos
	@mkdir -p logs/
	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Compiling: $(COLOR_FILE)$@$(COLOR_NONE)"
	$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ $< $(ARGS_LIBRARYS) $(ARGUMENTS)





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





################################################################
#                             REPO                             #
################################################################

REPOS_DIR := other/
REPOS = 

repos: repos_clone
	@$(FANCY_ECHO) "$(COLOR_REPO)$(FANCY_NAME): $(COLOR_TYPE)Compiling: $(COLOR_FILE)$@$(COLOR_NONE)"
	@$(foreach repo, $(REPOS), \
		$(MAKE) -C $(repo) -s ; \
	)

repos_all: repos_clone
	@$(foreach repo, $(REPOS), \
		$(MAKE) -C $(repo) -s all ; \
	)

repos_clean:
	@$(foreach repo, $(REPOS), \
		if [ -d $(repo) ] ; then \
			$(MAKE) -C $(repo) -s clean ; \
		fi ; \
	)

repos_fclean:
	@$(foreach repo, $(REPOS), \
		if [ -d $(repo) ] ; then \
			$(MAKE) -C $(repo) -s fclean ; \
		fi ; \
	)

repos_clone:
	@mkdir -p $(REPOS_DIR)
	@$(foreach repo, $(REPOS), \
		$(MAKE) $(repo)_clone -s ; \
	)

repos_rm:
	@$(foreach repo, $(REPOS), \
		$(MAKE) $(repo)_rm -s ; \
	)

.PHONY: repos repos_all repos_clean repos_fclean repos_clone repos_rm

################################################################





################################################################
#                            Engine                            #
################################################################

ENGINE_HTTPS := https://github.com/StaubMaster/CPP-GL-Engine.git
ENGINE_REPO := $(REPOS_DIR)/Engine

REPOS += $(ENGINE_REPO)
LIBRARYS += $(foreach library,$(shell $(MAKE) -C $(ENGINE_REPO) -s librarys),$(ENGINE_REPO)/$(library))
INCLUDES += $(foreach include,$(shell $(MAKE) -C $(ENGINE_REPO) -s includes),$(ENGINE_REPO)/$(include))
ARGUMENTS += $(foreach argument,$(shell $(MAKE) -C $(ENGINE_REPO) -s arguments),$(argument))

$(ENGINE_REPO)_clone :
	@if ! [ -d $(ENGINE_REPO) ] ; then \
		git clone $(ENGINE_HTTPS) $(ENGINE_REPO) -q ; \
	fi

$(ENGINE_REPO)_rm :
	@rm -rf $(ENGINE_REPO)

################################################################

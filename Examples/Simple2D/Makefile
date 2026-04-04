
NAME := Simple2D.exe

#COMPILER := c++ -std=c++11
COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror
REMOVER := rm -f

################################################################

BASE_DIR := ../../
include $(BASE_DIR)fancy.mk
FANCY_NAME := Simple2D

################################################################

OUTSIDE_DIR := ../
OUTSIDE_SRC := $(OUTSIDE_DIR)/_src/

################################################################

FILES_SRC := \
	../main.cpp \
	../FrameTime.cpp \
	../MainContext2D.cpp \
\
	$(OUTSIDE_SRC)/Graphics/Buffer/Element.cpp \
\
	$(OUTSIDE_SRC)/PolyGon/PolyGon.cpp \
	\
	$(OUTSIDE_SRC)/PolyGon/Graphics/Full/Main/Data.cpp \
	$(OUTSIDE_SRC)/PolyGon/Graphics/Full/Main/Buffer.cpp \
	$(OUTSIDE_SRC)/PolyGon/Graphics/Full/Shader.cpp \
	\
	$(OUTSIDE_SRC)/PolyGon/Graphics/Wire/Main/Buffer.cpp \
	$(OUTSIDE_SRC)/PolyGon/Graphics/Wire/Elem/Buffer.cpp \
	$(OUTSIDE_SRC)/PolyGon/Graphics/Wire/Shader.cpp \
	\
	$(OUTSIDE_SRC)/PolyGon/InstanceManager.cpp \
	$(OUTSIDE_SRC)/PolyGon/ObjectData.cpp \
	$(OUTSIDE_SRC)/PolyGon/Manager.cpp \
	$(OUTSIDE_SRC)/PolyGon/Object.cpp \
\
	main.cpp \

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

exe:
	@$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@mkdir -p logs/
	@$(MAKE) -s repos_all
	@$(MAKE) -s other_all
	@$(MAKE) -s $(FILES_OBJ)
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$(NAME))
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(FILES_OBJ) -o $(NAME) $(LIBRARYS) $(ARGUMENTS)

.PHONY: all clean fclean re exe

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
INCLUDES = . $(OUTSIDE_DIR)/_include
ARGUMENTS = 

ARGS_LIBRARYS = $(foreach library, $(LIBRARYS),$(library))
ARGS_INCLUDES = $(foreach include, $(INCLUDES),-I$(include))

################################################################

OTHER_DIR := $(BASE_DIR)/other/
include $(OTHER_DIR)/other.mk

REPOS_DIR := $(BASE_DIR)/repos/
include $(REPOS_DIR)/repos.mk

################################################################

logs_make:
	@mkdir -p logs/

logs_clean:
	@rm -r logs/
	@$(MAKE) -s logs_make

.PHONY: logs_make logs_clean

################################################################

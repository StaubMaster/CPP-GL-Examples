
NAME := Physics.exe

#COMPILER := c++ -std=c++11
COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror
REMOVER := rm -f

################################################################

BASE_DIR := ../../
include $(BASE_DIR)fancy.mk
FANCY_NAME := Physics

################################################################

FILES_SRC := \
	Graphics/Buffer/Element.cpp \
\
	Arrow2D/Main/Data.cpp \
	Arrow2D/Main/Buffer.cpp \
	Arrow2D/Inst/Data.cpp \
	Arrow2D/Inst/Buffer.cpp \
	Arrow2D/Buffer.cpp \
	Arrow2D/Shader.cpp \
	Arrow2D/Manager.cpp \
	Arrow2D/Data.cpp \
	Arrow2D/Object.cpp \
\
	Arrow2D/RankLengths.cpp \
\
	Inst2D/Buffer.cpp \
\
	PolyGon/Object.cpp \
	PolyGon/Graphics/Full/Data.cpp \
	PolyGon/Graphics/Full/Buffer.cpp \
	PolyGon/Graphics/Shader.cpp \
\
	WireFrame2D/WireFrame2D.cpp \
\
	Graphics2D/Wire/Buffer.cpp \
	Graphics2D/Wire/Shader.cpp \
\
	Physics2D/InstanceManager.cpp \
	Physics2D/Manager.cpp \
	Physics2D/IntrinsicData.cpp \
	Physics2D/ExtrinsicData.cpp \
	Physics2D/Object.cpp \
	Physics2D/Collision/ObjectProjection.cpp \
	Physics2D/Collision.cpp \
\
	SceneInteraction/Grid2D.cpp \
	SceneInteraction/Data.cpp \
	SceneInteraction/Base.cpp \
	SceneInteraction/Move.cpp \
	SceneInteraction/Spin.cpp \
	SceneInteraction/Force.cpp \
\
	FrameTime.cpp \
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
INCLUDES = .
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
	@$(REMOVER) logs/

.PHONY: logs_make logs_clean

################################################################

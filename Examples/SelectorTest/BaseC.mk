
#COMPILER := c++ -std=c++11 # normal
COMPILER := g++ -g -std=c++11 # debug
FLAGS := -Wall -Wextra -Werror
REMOVER := rm -f

################################################################

include $(BASE_DIR)fancy.mk

################################################################

DIR_SRC := .
DIR_OBJ := .

FILES_SRC := $(addprefix $(DIR_SRC)/,$(FILES))
FILES_OBJ := $(addprefix $(DIR_OBJ)/,$(FILES:.cpp=.o))

################################################################

# all            compile all
# final          compile only the final

# clean          delete parts
# clean-final    delete final
# fclean         delete fully

# re             recompile all
# re-final       recompile final

all:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s repos_all
	@$(MAKE) -s other_all
	@$(MAKE) -s $(FILES_OBJ)
	@$(MAKE) -s $(NAME)

clean:
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(FILES_OBJ)

fclean:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s clean
	@$(MAKE) -s clean-final

re:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY: all clean fclean re final

$(NAME) : $(FILES_OBJ) $(LIBRARYS)
	@$(MAKE) -s logs_make
	@$(call fancyNameCompilingEcho,$@)
#	@echo $(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(FILES_OBJ) -o $@ $(LIBRARYS) $(ARGUMENTS)
#	@echo
#	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(FILES_OBJ) -o $@ $(LIBRARYS) $(ARGUMENTS)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(FILES_OBJ) -o $@ $(LIBRARYS) $(ARGUMENTS)

################################################################

final:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s logs_make
	@$(MAKE) -s repos_all
	@$(MAKE) -s other_all
	@$(MAKE) -s $(FILES_OBJ)
	@$(call fancyNameCompilingEcho,$(NAME))
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) $(FILES_OBJ) -o $(NAME) $(LIBRARYS) $(ARGUMENTS)

clean-final:
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(NAME)

re-final:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s clean-final
	@$(MAKE) -s final

################################################################

%.o : %.cpp
	@$(call fancyNameCompilingEcho,$@)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ -c $<

################################################################

LIBRARYS := 
INCLUDES := . $(OUTSIDE_DIR)/_include
ARGUMENTS := 

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

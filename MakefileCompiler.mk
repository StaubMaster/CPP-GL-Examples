
################################################################

#COMPILER := c++ -std=c++11 # normal
COMPILER := g++ -g -std=c++11 # debug
FLAGS := -Wall -Wextra -Werror
REMOVER := rm -f

################################################################

FILES_SRC := $(addprefix $(DIR_SRC)/,$(FILES))
FILES_OBJ := $(addprefix $(DIR_OBJ)/,$(FILES:.cpp=.o))

################################################################

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

.PHONY: all clean fclean re

################################################################

final:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s logs_make
	@$(MAKE) -s repos_all
	@$(MAKE) -s other_all
	@$(MAKE) -s $(FILES_OBJ)
	@$(call fancyNameCompilingEcho,$(NAME))
	@$(COMPILER) $(FLAGS) $(addprefix -I,$(INCLUDES)) $(FILES_OBJ) -o $(NAME) $(LIBRARYS) $(ARGUMENTS)

clean-final:
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(NAME)

re-final:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s clean-final
	@$(MAKE) -s final

.PHONY: final clean-final re-final

################################################################

$(NAME) : $(FILES_OBJ) $(LIBRARYS)
	@$(MAKE) -s logs_make
	@$(call fancyNameCompilingEcho,$@)
	@$(COMPILER) $(FLAGS) $(addprefix -I,$(INCLUDES)) $(FILES_OBJ) -o $(NAME) $(LIBRARYS) $(LIBRARYS) $(ARGUMENTS)

%.o : %.cpp
	@$(call fancyNameCompilingEcho,$@)
	@$(COMPILER) $(FLAGS) $(addprefix -I,$(INCLUDES)) -o $@ -c $<

################################################################

logs_make:
	@mkdir -p logs/

logs_clean:
	@rm -r logs/
	@$(MAKE) -s logs_make

.PHONY: logs_make logs_clean

################################################################

include $(OTHER_DIR)/other.mk
include $(REPOS_DIR)/repos.mk

################################################################

ifndef NAME
$(error NAME is not set)
endif

ifndef FANCY_NAME
$(error FANCY_NAME is not set)
endif

ifndef FILES
$(error FILES is not set)
endif

ifndef DIR_SRC
$(error DIR_SRC is not set)
endif

ifndef DIR_OBJ
$(error DIR_OBJ is not set)
endif

################################################################

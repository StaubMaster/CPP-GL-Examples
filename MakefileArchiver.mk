
################################################################

#COMPILER := c++ -std=c++11 # normal
COMPILER := g++ -g -std=c++11 # debug
FLAGS := -Wall -Wextra -Werror
ARCHIVER := ar -rcs
REMOVER := rm -f

################################################################

FILES_SRC := $(addprefix $(DIR_SRC)/,$(FILES))
FILES_OBJ := $(addprefix $(DIR_OBJ)/,$(FILES:.cpp=.o))

################################################################

all:
	@$(call fancyNameTargetEcho,$@)
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

################################################################

final:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s $(FILES_OBJ)
	@$(call fancyNameCompilingEcho,$(NAME))
	@$(ARCHIVER) $(NAME) $(FILES_OBJ)

clean-final:
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(NAME)

re-final:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s clean-final
	@$(MAKE) -s final

################################################################

$(NAME) : $(FILES_OBJ)
	@$(call fancyNameCompilingEcho,$@)
	@$(ARCHIVER) $(NAME) $(FILES_OBJ)

%.o : %.cpp
	@$(call fancyNameCompilingEcho,$@)
	@$(COMPILER) $(FLAGS) $(addprefix -I,$(INCLUDES)) -o $@ -c $<

################################################################

include $(OTHER_DIR)/other.mk
include $(REPOS_DIR)/repos.mk

################################################################

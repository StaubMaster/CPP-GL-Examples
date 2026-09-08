
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
	@$(REMOVER) $(FILES_OBJ)
	@$(REMOVER) $(NAME)

re:
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(FILES_OBJ)
	@$(REMOVER) $(NAME)
	@$(MAKE) -s $(FILES_OBJ)
	@$(MAKE) -s $(NAME)

.PHONY: all clean fclean re final

################################################################

final:
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s $(NAME)

clean-final:
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(NAME)

re-final:
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(NAME)
	@$(MAKE) -s $(NAME)

################################################################

$(NAME) : $(FILES_OBJ)
	@$(call fancyNameArchivingEcho,$@)
	@$(ARCHIVER) $(NAME) $(FILES_OBJ)

%.o : %.cpp
	@$(call fancyNameCompilingEcho,$@)
	@$(COMPILER) $(FLAGS) $(addprefix -I,$(INCLUDES)) -o $@ -c $<

################################################################

include $(OTHER_DIR)/other.mk
include $(REPOS_DIR)/repos.mk

################################################################

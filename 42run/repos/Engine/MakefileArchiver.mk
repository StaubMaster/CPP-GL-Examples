
################################################################

COMPILER_C := cc -fPIE

#COMPILER_CPP := c++ -std=c++11 # normal
COMPILER_CPP := g++ -g -std=c++11 # debug

FLAGS := -Wall -Wextra -Werror

ARCHIVER := ar -rcs

REMOVER := rm -f

################################################################

include $(BASE_DIR)/fancy.mk

################################################################

FILES_SRC := $(addprefix $(DIR_SRC)/,$(FILES))
FILES_OBJ := $(addprefix $(DIR_OBJ)/,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(FILES))))

################################################################

all:
	@$(MAKE) -s other_all
	@$(call fancyNameTargetEcho,$@)
	@$(MAKE) -s $(FILES_OBJ)
	@$(MAKE) -s $(NAME)

clean:
	@$(MAKE) -s other_clean
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(FILES_OBJ)

fclean:
	@$(MAKE) -s other_fclean
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(FILES_OBJ)
	@$(REMOVER) $(NAME)

re:
	@$(MAKE) -s other_re
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(FILES_OBJ)
	@$(REMOVER) $(NAME)
	@$(MAKE) -s $(FILES_OBJ)
	@$(MAKE) -s $(NAME)

.PHONY: all clean fclean re

################################################################

final:
	@$(call fancyNameTargetEcho,$@)
	@$(ARCHIVER) $(NAME) $(FILES_OBJ)

clean-final:
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(NAME)

re-final:
	@$(call fancyNameTargetEcho,$@)
	@$(REMOVER) $(NAME)
	@$(MAKE) -s $(NAME)

.PHONY: final clean-final re-final

################################################################

$(NAME) : $(FILES_OBJ)
	@$(call fancyNameArchivingEcho,$@)
	@$(ARCHIVER) $(NAME) $(FILES_OBJ)

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c
	@$(call fancyNameCompilingEcho,$@)
	@mkdir -p $(dir $@)
	@$(COMPILER_C) $(FLAGS) $(addprefix -I,$(INCLUDES)) $(ARGUMENTS) -c $^ -o $@

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.cpp
	@$(call fancyNameCompilingEcho,$@)
	@mkdir -p $(dir $@)
	@$(COMPILER_CPP) $(FLAGS) $(addprefix -I,$(INCLUDES)) $(ARGUMENTS) -o $@ -c $<

################################################################

include $(BASE_DIR)/other.mk

################################################################

ifndef BASE_DIR
$(error missing BASE_DIR)
endif

ifndef NAME
$(error missing NAME)
endif

ifndef FANCY_NAME
$(error missing FANCY_NAME)
endif

ifndef FILES
$(error missing FILES)
endif

################################################################

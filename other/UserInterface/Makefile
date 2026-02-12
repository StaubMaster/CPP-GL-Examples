
NAME := UserInterface.a

COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror
ARCHIVER := ar -rcs
REMOVER := rm -f



FANCY_NAME := UserInterface
include ../../fancy.mk



DIR_SRC := ./
DIR_OBJ := ./

FILES_SRC := \
	$(DIR_SRC)/Anchor1D.cpp \
	$(DIR_SRC)/Anchor2D.cpp \
\
	$(DIR_SRC)/Control/Base/Data.cpp \
	$(DIR_SRC)/Control/Base/Buffer.cpp \
	$(DIR_SRC)/Control/Base/Shader.cpp \
	$(DIR_SRC)/Control/Base/Manager.cpp \
	$(DIR_SRC)/Control/Base/Base.cpp \
\
	$(DIR_SRC)/Control/Window.cpp \
	$(DIR_SRC)/Control/Form.cpp \
	$(DIR_SRC)/Control/GroupBox.cpp \
	$(DIR_SRC)/Control/Button.cpp \
	$(DIR_SRC)/Control/TextBox.cpp \
	$(DIR_SRC)/Control/Slider.cpp \
	$(DIR_SRC)/Control/CheckBox.cpp \
\
	$(DIR_SRC)/Text/Data.cpp \
	$(DIR_SRC)/Text/Buffer.cpp \
	$(DIR_SRC)/Text/Shader.cpp \
	$(DIR_SRC)/Text/Manager.cpp \
	$(DIR_SRC)/Text/Font/Font.cpp \
	$(DIR_SRC)/Text/Font/Template.cpp \
	$(DIR_SRC)/Text/Font/Parsing.cpp

FILES_OBJ := $(FILES_SRC:$(DIR_SRC)%=$(DIR_OBJ)%)
FILES_OBJ := $(FILES_OBJ:.cpp=.o)



all:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s $(FILES_OBJ)
	@$(MAKE) -s $(NAME)

clean:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@rm -f $(FILES_OBJ)

fclean:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s clean
	@rm -f $(NAME)

re:
	$(call fancyEcho,$(FANCY_NAME),Target,$@)
	@$(MAKE) -s fclean
	@$(MAKE) -s all

.PHONY: all clean fclean re



$(NAME) : $(FILES_OBJ)
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@$(ARCHIVER) $(NAME) $(FILES_OBJ)

$(DIR_OBJ)%.o : $(DIR_SRC)%.cpp
	@$(call fancyEcho,$(FANCY_NAME),Compiling,$@)
	@$(COMPILER) $(FLAGS) $(ARGS_INCLUDES) -o $@ -c $<



LIBRARYS = 
INCLUDES = .
ARGUMENTS = 

ARGS_LIBRARYS = $(foreach library, $(LIBRARYS),$(library))
ARGS_INCLUDES = $(foreach include, $(INCLUDES),-I$(include))

REPOS_DIR := ../../repos/
include $(REPOS_DIR)/repos.mk

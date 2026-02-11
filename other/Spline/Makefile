
NAME := Spline.a

COMPILER := g++ -g -std=c++11
FLAGS := -Wall -Wextra -Werror
ARCHIVER := ar -rcs
REMOVER := rm -f



FANCY_NAME := Spline
include ../../fancy.mk



DIR_SRC := ./
DIR_OBJ := ./

FILES_SRC := \
	$(DIR_SRC)/SplineNode3D.cpp \
	$(DIR_SRC)/SplineSegment3D.cpp \
	$(DIR_SRC)/SplineCurve3D.cpp \
	$(DIR_SRC)/SplineObject.cpp \
\
	$(DIR_SRC)/InterPolator3D.cpp \
	$(DIR_SRC)/ChainNeighbours3D.cpp \
	$(DIR_SRC)/CubicSpline3D.cpp \
	$(DIR_SRC)/CubicSplineCurve3D.cpp

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
INCLUDES = ../
ARGUMENTS = 

ARGS_LIBRARYS = $(foreach library, $(LIBRARYS),$(library))
ARGS_INCLUDES = $(foreach include, $(INCLUDES),-I$(include))

REPOS_DIR := ../../repos/
include $(REPOS_DIR)/repos.mk

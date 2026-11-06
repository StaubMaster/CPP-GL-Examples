
NAME := UserInterface.exe
FANCY_NAME := UserInterface

################################################################

FILES := \
	Context.cpp \
\
	Test/Selector.cpp \
	Test/TileGrid.cpp \
	Test/Text.cpp \
	Test/Graph.cpp \
	Test/Scroll.cpp \
	Test/List.cpp \
\
	Form/DirectoryNavigator.cpp \
\
	new.cpp \
	main.cpp \

DIR_SRC := .
DIR_OBJ := .

LIBRARYS :=
INCLUDES := .
ARGUMENTS :=

################################################################

allall: all

BASE_DIR := ../../
OTHER_DIR := $(BASE_DIR)/other/
REPOS_DIR := $(BASE_DIR)/repos/
include $(BASE_DIR)fancy.mk

################################################################

include $(OTHER_DIR)/Miscellaneous.mk
include $(OTHER_DIR)/UserInterface.mk

include $(REPOS_DIR)/Engine.mk

################################################################

include $(BASE_DIR)/MakefileCompiler.mk

################################################################

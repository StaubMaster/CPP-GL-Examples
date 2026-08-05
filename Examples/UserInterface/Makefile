
NAME := UserInterface.exe
FANCY_NAME := UserInterface

################################################################

FILES := \
	Context.cpp \
	Menu0.cpp \
	Menu1.cpp \
	Menu2.cpp \
	Menu3.cpp \
	TestScroll.cpp \
\
	Control/ScrollBox.cpp \
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
include $(REPOS_DIR)/FileManager.mk
include $(REPOS_DIR)/OpenGL.mk

################################################################

include $(BASE_DIR)/MakefileCompiler.mk

################################################################

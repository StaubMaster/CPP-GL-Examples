
NAME := PolyHedraDisplay.exe
FANCY_NAME := PolyHedraDisplay

################################################################

FILES := \
	main.cpp

DIR_SRC := .
DIR_OBJ := .

LIBRARYS :=
INCLUDES := . ..
ARGUMENTS :=

################################################################

allall: all

BASE_DIR := ../../
OTHER_DIR := $(BASE_DIR)/other/
REPOS_DIR := $(BASE_DIR)/repos/
include $(BASE_DIR)fancy.mk

################################################################

include $(OTHER_DIR)/UserInterface.mk

include $(REPOS_DIR)/Engine.mk
include $(REPOS_DIR)/FileManager.mk
include $(REPOS_DIR)/OpenGL.mk

################################################################

#include $(BASE_DIR)/MakefileArchiver.mk
include $(BASE_DIR)/MakefileCompiler.mk

################################################################



NAME := Test.exe
FANCY_NAME := Test

################################################################

FILES := \
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

#include $(OTHER_DIR)/Miscellaneous.mk

#include $(REPOS_DIR)/Engine.mk

################################################################

include $(BASE_DIR)/MakefileCompiler.mk

################################################################

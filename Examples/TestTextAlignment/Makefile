
NAME := TestTextAlignment.a
FANCY_NAME := TestTextAlignment

################################################################

FILES := \
	TestTextAlignment.cpp \

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

include $(BASE_DIR)/MakefileArchiver.mk

################################################################


NAME := UserInterface.a
FANCY_NAME := UserInterface

################################################################

FILES := \
	UserInterfaceContext.cpp \
	UserInterfaceMenu0.cpp \
	UserInterfaceMenu1.cpp \
	UserInterfaceMenu2.cpp \
	UserInterfaceMenu3.cpp \
	new.cpp \

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

include $(OTHER_DIR)/Miscellaneous.mk
include $(OTHER_DIR)/UserInterface.mk

include $(REPOS_DIR)/Engine.mk
include $(REPOS_DIR)/FileManager.mk
include $(REPOS_DIR)/OpenGL.mk

################################################################

include $(BASE_DIR)/MakefileArchiver.mk

################################################################

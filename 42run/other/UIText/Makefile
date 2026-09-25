
NAME := UIText.a
FANCY_NAME := UIText

################################################################

FILES := \
	Data.cpp \
	Buffer.cpp \
	ShaderLayout.cpp \
	Manager.cpp \
	ObjectData.cpp \
	Object.cpp \
	Font/Font.cpp \
	Font/Parsing.cpp \

DIR_SRC := .
DIR_OBJ := .

LIBRARYS :=
INCLUDES := ../
ARGUMENTS :=

################################################################

allall: all

BASE_DIR := ../../
OTHER_DIR := $(BASE_DIR)/other/
REPOS_DIR := $(BASE_DIR)/repos/
include $(BASE_DIR)fancy.mk

################################################################

include $(REPOS_DIR)/Engine.mk

################################################################

include $(BASE_DIR)/MakefileArchiver.mk

################################################################


NAME := ValueGen.a
FANCY_NAME := ValueGen

################################################################

FILES := \
	ValueGen/Random.cpp \
	ValueGen/Lerp.cpp \
	ValueGen/Perlin2D.cpp \
	ValueGen/Perlin3D.cpp \
	ValueGen/Simplex2D.cpp \

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

include $(REPOS_DIR)/Engine.mk

################################################################

include $(BASE_DIR)/MakefileArchiver.mk

################################################################


NAME := NewPolyHedra.a
FANCY_NAME := NewPolyHedra

################################################################

FILES := \
\
	NewPolyHedra/Pallet/.cpp \
	NewPolyHedra/Pallet/Full/Layout.cpp \
	NewPolyHedra/Pallet/Wire/Layout.cpp \
	NewPolyHedra/Pallet/Manager.cpp \
	\
	NewPolyHedra/Base/Logical/Object.cpp \
	NewPolyHedra/Base/Logical/ObjectManager.cpp \
	NewPolyHedra/Base/Display/Object.cpp \
	NewPolyHedra/Base/Display/ObjectManager.cpp \
	NewPolyHedra/Base/Manager.cpp \
	\
	NewPolyHedra/Manager.cpp \
\
	Special/Basic3D/Display/Data.cpp \
	Special/Basic3D/Special.cpp \
	Special/Basic3D/Layout.cpp \
	\
	Special/TransScaleColor3D/Display/Data.cpp \
	Special/TransScaleColor3D/Special.cpp \
	Special/TransScaleColor3D/Layout.cpp \

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

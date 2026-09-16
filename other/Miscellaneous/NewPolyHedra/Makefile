
NAME := NewPolyHedra.a
FANCY_NAME := NewPolyHedra

################################################################

FILES := \
\
	Manager.cpp \
	ObjectManager.cpp \
	Pallet.cpp \
	Pallet/Full/Layout.cpp \
	Pallet/Wire/Layout.cpp \
	PalletManager.cpp \
	PalletObjectData.cpp \
	PalletObjectManager.cpp \
\
	DataType/Basic3D/Layout.cpp \
	DataType/Basic3D/InstanceData.cpp \
	DataType/Basic3D/Special.cpp \
	\
	DataType/TransScaleColor3D/Layout.cpp \
	DataType/TransScaleColor3D/InstanceData.cpp \
	DataType/TransScaleColor3D/Special.cpp \

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

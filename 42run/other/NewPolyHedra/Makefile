
NAME := NewPolyHedra.a
FANCY_NAME := NewPolyHedra

################################################################

FILES := \
\
	NewPolyHedra/Manager.cpp \
	NewPolyHedra/ObjectManager.cpp \
	NewPolyHedra/Pallet.cpp \
	NewPolyHedra/Pallet/Full/Layout.cpp \
	NewPolyHedra/Pallet/Wire/Layout.cpp \
	NewPolyHedra/PalletManager.cpp \
	NewPolyHedra/PalletObjectData.cpp \
	NewPolyHedra/PalletObjectManager.cpp \
\
	NewPolyHedra/DataType/Basic3D/Layout.cpp \
	NewPolyHedra/DataType/Basic3D/InstanceData.cpp \
	NewPolyHedra/DataType/Basic3D/Special.cpp \
	\
	NewPolyHedra/DataType/TransScaleColor3D/Layout.cpp \
	NewPolyHedra/DataType/TransScaleColor3D/InstanceData.cpp \
	NewPolyHedra/DataType/TransScaleColor3D/Special.cpp \

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

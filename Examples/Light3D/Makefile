
NAME := Light3D.a
FANCY_NAME := Light3D

################################################################

FILES := \
	PropertyControl/PropertyControl.cpp \
	PropertyControl/VectorF3.cpp \
	PropertyControl/EulerAngle3D.cpp \
	PropertyControl/ColorF4.cpp \
	PropertyControl/Trans3D.cpp \
	PropertyControl/LightBase.cpp \
	PropertyControl/LightSpot.cpp \
	\
	UI/PolyHedraObject.cpp \
	UI/SpotLightEntry.cpp \
	\
	LightShaderLayout.cpp \
	SpotLightEntry.cpp \
	\
	Ray3D_Hit.cpp \
	\
	Context.cpp \
	new.cpp

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


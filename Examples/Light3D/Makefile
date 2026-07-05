
NAME := Light3D.a
FANCY_NAME := Light3D

################################################################

FILES := \
	\
	Ray3D_Hit.cpp \
	UserTrans3DChange.cpp \
	SceneParsingData.cpp \
	\
	PropertyControl/PropertyControl.cpp \
	PropertyControl/VectorF3.cpp \
	PropertyControl/EulerAngle3D.cpp \
	PropertyControl/ColorF4.cpp \
	PropertyControl/Trans3D.cpp \
	PropertyControl/LightBase.cpp \
	PropertyControl/LightDirection.cpp \
	PropertyControl/LightSpot.cpp \
	\
	LightShaderLayout.cpp \
	\
	SceneObject/SceneObject.cpp \
	SceneObject/PolyHedraObject.cpp \
	SceneObject/LightAmbient.cpp \
	SceneObject/LightDirection.cpp \
	SceneObject/LightSpot.cpp \
	SceneObject/UI/SceneObject.cpp \
	SceneObject/UI/PolyHedraObject.cpp \
	\
	NewPolyHedra/Manager.cpp \
	NewPolyHedra/ObjectData.cpp \
	NewPolyHedra/ObjectManager.cpp \
	NewPolyHedra/Pallet.cpp \
	NewPolyHedra/PalletManager.cpp \
	NewPolyHedra/PalletObjectData.cpp \
	NewPolyHedra/PalletObjectManager.cpp \
	\
	NewPolyHedra/DataType/Basic3D/Layout.cpp \
	NewPolyHedra/DataType/Basic3D/ObjectData.cpp \
	NewPolyHedra/DataType/TransScaleColor3D/Layout.cpp \
	NewPolyHedra/DataType/TransScaleColor3D/ObjectData.cpp \
	\
	UI_Control_List.cpp \
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


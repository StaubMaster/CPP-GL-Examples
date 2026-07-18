
NAME := Light3D.exe
FANCY_NAME := Light3D

################################################################

FILES := \
	UserTrans3DChange.cpp \
	SceneParsingData.cpp \
	\
	LightShaderLayout.cpp \
	\
	SceneObject/SceneObject.cpp \
	SceneObject/PolyHedraObject.cpp \
	SceneObject/LightAmbient.cpp \
	SceneObject/LightDirection.cpp \
	SceneObject/LightPoint.cpp \
	SceneObject/LightSpot.cpp \
	SceneObject/UI/SceneObject.cpp \
	SceneObject/UI/PolyHedraObject.cpp \
\
	NewPolyHedraDataType/Basic3D/Layout.cpp \
	NewPolyHedraDataType/Basic3D/ObjectData.cpp \
	NewPolyHedraDataType/Basic3D/Special.cpp \
	NewPolyHedraDataType/TransScaleColor3D/Layout.cpp \
	NewPolyHedraDataType/TransScaleColor3D/ObjectData.cpp \
	NewPolyHedraDataType/TransScaleColor3D/Special.cpp \
\
	Ray3D_Hit.cpp \
\
	UI_Control_List.cpp \
	Context.cpp \
	new.cpp \
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

include $(OTHER_DIR)/Miscellaneous.mk
include $(OTHER_DIR)/UserInterface.mk

include $(REPOS_DIR)/Engine.mk
include $(REPOS_DIR)/FileManager.mk
include $(REPOS_DIR)/OpenGL.mk

################################################################

include $(BASE_DIR)/MakefileCompiler.mk

################################################################


NAME := Editor3D.exe
FANCY_NAME := Editor3D

################################################################

FILES := \
	LightManager.cpp \
\
	Layout/Shader.cpp \
	Layout/Multiform.cpp \
	Layout/Parser/Uniform.cpp \
	Layout/Parser/Attribute.cpp \
\
	SceneObject/SceneObject.cpp \
	SceneObject/DisplayMode.cpp \
	SceneObject/Collection.cpp \
	\
	SceneObject/PolyHedraObject.cpp \
	SceneObject/LightAmbient.cpp \
	SceneObject/LightDirection.cpp \
	SceneObject/LightPoint.cpp \
	SceneObject/LightSpot.cpp \
	SceneObject/UI/SceneObject.cpp \
	SceneObject/UI/PolyHedraObject.cpp \
	\
	SceneParsingData.cpp \
\
	Ray3D_Hit.cpp \
\
	UI/ListForm.cpp \
	UI/Change3D/Base.cpp \
	UI/Change3D/VectorF3.cpp \
	UI/Change3D/EulerAngle3D.cpp \
\
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

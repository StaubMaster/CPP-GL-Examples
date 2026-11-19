
NAME := Editor3D.exe
FANCY_NAME := Editor3D

################################################################

FILES := \
	Ray3D_Hit.cpp \
\
	NewPolyHedra/Init/Basic3D.cpp \
	NewPolyHedra/Init/TransScaleColor3D.cpp \
	\
	NewPolyHedra/UserInterface/Display/Data.cpp \
	NewPolyHedra/UserInterface/Layout.cpp \
	NewPolyHedra/UserInterface/Special.cpp \
	NewPolyHedra/UserInterface/Init.cpp \
\
	SceneObject/.cpp \
	SceneObject/DisplayMode.cpp \
	SceneObject/Collection.cpp \
	SceneObject/Manager.cpp \
	\
	SceneObject/PolyHedraObject.cpp \
	SceneObject/LightAmbient.cpp \
	SceneObject/LightDirection.cpp \
	SceneObject/LightPoint.cpp \
	SceneObject/LightSpot.cpp \
	SceneObject/UI/SceneObject.cpp \
	\
	SceneObject/Parsing.cpp \
\
	Change3D/General/Base.cpp \
	Change3D/General/Collection.cpp \
	Change3D/VectorF3.cpp \
	Change3D/EulerAngle3D.cpp \
	Change3D/Trans3D.cpp \
\
	UI/PolyHedra/PolyHedraEntry.cpp \
	UI/PolyHedra/Pallet.cpp \
	UI/PolyHedra/Basic3D/LogicalObject.cpp \
	UI/PolyHedra/Basic3D/DisplayObject.cpp \
	\
	UI/ListForm.cpp \
\
	Context.cpp \
	main.cpp \

DIR_SRC := ./code/
DIR_OBJ := ./code/

LIBRARYS :=
INCLUDES := ./code/
ARGUMENTS :=

################################################################

allall: all

BASE_DIR := ../../
OTHER_DIR := $(BASE_DIR)/other/
REPOS_DIR := $(BASE_DIR)/repos/
include $(BASE_DIR)fancy.mk

################################################################

include $(REPOS_DIR)/Engine.mk

include $(OTHER_DIR)/UserInterface.mk
include $(OTHER_DIR)/Miscellaneous.mk
include $(OTHER_DIR)/NewPolyHedra.mk

################################################################

include $(BASE_DIR)/MakefileCompiler.mk

################################################################

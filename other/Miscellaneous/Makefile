
NAME := Miscellaneous.a
FANCY_NAME := Miscellaneous

################################################################

FILES := \
	ContextBase.cpp \
	AuxThreadBase.cpp \
\
	ValueGen/Random.cpp \
	ValueGen/Perlin2D.cpp \
	ValueGen/Perlin3D.cpp \
\
	ValueTypeUI/PropertyControl.cpp \
	ValueTypeUI/VectorF3.cpp \
	ValueTypeUI/EulerAngle3D.cpp \
	ValueTypeUI/ColorF4.cpp \
	ValueTypeUI/Trans3D.cpp \
	ValueTypeUI/LightBase.cpp \
	ValueTypeUI/LightDirection.cpp \
	ValueTypeUI/LightSpot.cpp \
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
\
	Telemetry/Time.cpp \
	Telemetry/StopWatch.cpp \
	Telemetry/WaitDoTime.cpp \
\
	Axis/Enums.cpp \
	Axis/Orientation.cpp \
\
	CenterIndexLoop/2D.cpp \
	CenterIndexLoop/3D.cpp \
\
	ContainerLock/Lock.cpp \
	ContainerLock/AccessGuard.cpp \
	ContainerLock/AssignGuard.cpp \
\
	GridCast/GridCast3D.cpp \
\
	PhysicsContext.cpp \
\
	UnitToString.cpp \

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

include $(OTHER_DIR)/UserInterface.mk

include $(REPOS_DIR)/Engine.mk
include $(REPOS_DIR)/FileManager.mk
include $(REPOS_DIR)/OpenGL.mk

################################################################

include $(BASE_DIR)/MakefileArchiver.mk

################################################################

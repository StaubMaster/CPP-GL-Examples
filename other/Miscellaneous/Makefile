
NAME := Miscellaneous.a
FANCY_NAME := Miscellaneous

################################################################

FILES := \
	ContextBase.cpp \
\
	Light/Manager.cpp \
\
	Layout/Uniform/Display.cpp \
	Layout/Uniform/View3D.cpp \
	Layout/Uniform/Light3D.cpp \
	\
	Layout/Multiform/Display.cpp \
	Layout/Multiform/View3D.cpp \
	Layout/Multiform/Light3D.cpp \
\
	UI/NestedProperty.cpp \
	UI/ValueType/VectorF3.cpp \
	UI/ValueType/EulerAngle3D.cpp \
	UI/ValueType/ColorF4.cpp \
	UI/ValueType/Trans3D.cpp \
	UI/ValueType/LightBase.cpp \
	UI/ValueType/LightDirection.cpp \
	UI/ValueType/LightSpot.cpp \
\
	Telemetry/Time.cpp \
	Telemetry/StopWatch.cpp \
	Telemetry/WaitDoTime.cpp \
\
	Axis/3D/Orientation.cpp \
	Axis/3D/Funcs.cpp \
	Axis/3D/Show.cpp \
	\
	Axis/2D/Orientation.cpp \
	Axis/2D/Show.cpp \
\
	CenterIndexLoop/2D.cpp \
	CenterIndexLoop/3D.cpp \
\
	Threading/Lock.cpp \
	Threading/Guard/Access/Unique.cpp \
	Threading/Guard/Access/Shared.cpp \
	Threading/Guard/Assign/Unique.cpp \
	Threading/Guard/Assign/Shared.cpp \
	\
	Threading/Thread/Loop/Base.cpp \
	Threading/Thread/Loop/Idle.cpp \
	Threading/Thread/Loop/Tick.cpp \
	Threading/Thread/Loop/Collection.cpp \
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

################################################################

include $(BASE_DIR)/MakefileArchiver.mk

################################################################

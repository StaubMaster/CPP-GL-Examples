
NAME := Miscellaneous.a
FANCY_NAME := Miscellaneous

################################################################

FILES := \
	ContextBase.cpp \
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
	Threading/ObjectLock.cpp \
	Threading/ObjectAccessUniqueGuard.cpp \
	Threading/ObjectAccessSharedGuard.cpp \
	Threading/ObjectAssignUniqueGuard.cpp \
	Threading/ObjectAssignSharedGuard.cpp \
	\
	IdleLoopThread.cpp \
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


NAME := Selector.exe
FANCY_NAME := Selector

################################################################

FILES := \
	General/ContextBase.cpp \
	General/AuxThreadBase.cpp \
\
	General/ValueGen/Random.cpp \
	General/ValueGen/Perlin2D.cpp \
	General/ValueGen/Perlin3D.cpp \
\
	General/Telemetry/Time.cpp \
	General/Telemetry/StopWatch.cpp \
	General/Telemetry/WaitDoTime.cpp \
\
	General/Axis/Enums.cpp \
	General/Axis/Orientation.cpp \
\
	General/UnitToString.cpp \
\
	General/CenterIndexLoop/2D.cpp \
	General/CenterIndexLoop/3D.cpp \
\
	General/ContainerLock/Lock.cpp \
	General/ContainerLock/AccessGuard.cpp \
	General/ContainerLock/AssignGuard.cpp \
\
	General/GridCast/GridCast3D.cpp \
\
	General/PhysicsContext.cpp \
\
	main.cpp \

DIR_SRC := .
DIR_OBJ := .

LIBRARYS :=
INCLUDES := .
ARGUMENTS :=

################################################################

allall: all

BASE_DIR := ../
OTHER_DIR := $(BASE_DIR)/other/
REPOS_DIR := $(BASE_DIR)/repos/
include $(BASE_DIR)fancy.mk

################################################################

include Selector.mk
include UserInterface.mk
include NoisePlane.mk
include Light3D.mk

include $(OTHER_DIR)/UserInterface.mk

include $(REPOS_DIR)/Engine.mk
include $(REPOS_DIR)/FileManager.mk
include $(REPOS_DIR)/OpenGL.mk

################################################################

include $(BASE_DIR)/MakefileCompiler.mk

################################################################

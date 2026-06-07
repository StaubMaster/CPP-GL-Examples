
NAME := NoisePlane.a
FANCY_NAME := NoisePlane

################################################################

#	Plane/Plane.cpp \
#	Plane/PlaneValue.cpp \
#	Plane/PlaneNeighbours.cpp \
#	Plane/PlaneGraphics.cpp \
#	Plane/PlaneManager.cpp \

FILES := \
	Graphics/Main/Data.cpp \
	Graphics/Main/Buffer.cpp \
	Graphics/Inst/Data.cpp \
	Graphics/Inst/Buffer.cpp \
	Graphics/Buffer.cpp \
	Graphics/ShaderLayout.cpp \
	Graphics/MultiBufferChunkU.cpp \
\
	Axis/Enums.cpp \
	Axis/Orientation.cpp \
\
	Voxel.cpp \
	Voxel/GraphicsData.cpp \
	Voxel/GeometryPallet.cpp \
	Voxel/Pallet.cpp \
\
	Chunk.cpp \
	Chunk/GraphicsData.cpp \
	Chunk/Neighbours.cpp \
	Chunk/Manager.cpp \
\
	VoxelHit.cpp \
	ChunkVoxelIndex.cpp \
	Structure.cpp \
\
	AuxThread/AuxThread1.cpp \
	AuxThread/AuxThread2.cpp \
	AuxThread/AuxThread3.cpp \
\
	CenterIndexLoop/2D.cpp \
	CenterIndexLoop/3D.cpp \
\
	ContainerLock/Lock.cpp \
	ContainerLock/AccessGuard.cpp \
	ContainerLock/AssignGuard.cpp \
\
	BoxEntity.cpp \
\
	GridCast/GridCast3D.cpp \
\
	Menus/Main.cpp \
	Menus/Pause.cpp \
	Menus/Options.cpp \
	Menus/Debug.cpp \
\
	Item/ItemBase.cpp \
	Item/ItemVoxel.cpp \
	Item/ItemContainer.cpp \
	\
	Menus/Item/InventorySlot.cpp \
	Menus/Item/Inventory.cpp \
	Menus/Item/HotBar.cpp \
\
	PhysicsContext.cpp \
	ContextNoisePlane.cpp \

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

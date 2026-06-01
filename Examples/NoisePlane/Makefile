
NAME := NoisePlane.a
FANCY_NAME := NoisePlane

################################################################

#	Plane/Plane.cpp \
#	Plane/PlaneValue.cpp \
#	Plane/PlaneNeighbours.cpp \
#	Plane/PlaneGraphics.cpp \
#	Plane/PlaneManager.cpp \

FILES := \
	Voxel/Graphics/Main/Data.cpp \
	Voxel/Graphics/Main/Buffer.cpp \
	Voxel/Graphics/Inst/Data.cpp \
	Voxel/Graphics/Inst/Buffer.cpp \
	Voxel/Graphics/Buffer.cpp \
	Voxel/Graphics/ShaderLayout.cpp \
	Voxel/Graphics/MultiBufferChunkU.cpp \
	\
	Voxel/Voxel.cpp \
	Voxel/VoxelGraphicsData.cpp \
	Voxel/VoxelGeometryPallet.cpp \
	Voxel/VoxelPallet.cpp \
	Voxel/AxisOrientation.cpp \
	Voxel/AxisEnums.cpp \
	Voxel/VoxelHit.cpp \
	\
	Voxel/ChunkGraphicsData.cpp \
	Voxel/ChunkVoxelIndex.cpp \
	Voxel/Chunk.cpp \
	Voxel/AccessLockedChunk.cpp \
	Voxel/AssignLockedChunk.cpp \
	Voxel/ChunkNeighbours.cpp \
	Voxel/ChunkManager.cpp \
	\
	Voxel/Structure.cpp \
	\
	AuxThread1.cpp \
	AuxThread2.cpp \
	AuxThread3.cpp \
	\
	CenterIndexLoop2D.cpp \
	CenterIndexLoop3D.cpp \
	\
	ContainerLock.cpp \
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


NAME := NoisePlane.a
FANCY_NAME := NoisePlane

################################################################

#	Plane/Plane.cpp \
#	Plane/PlaneValue.cpp \
#	Plane/PlaneNeighbours.cpp \
#	Plane/PlaneGraphics.cpp \
#	Plane/PlaneManager.cpp \

FILES := \
	Voxel/Graphics/Voxel.cpp \
	Voxel/Graphics/Main/Data.cpp \
	Voxel/Graphics/Main/Buffer.cpp \
	Voxel/Graphics/Inst/Data.cpp \
	Voxel/Graphics/Inst/Buffer.cpp \
	Voxel/Graphics/Buffer.cpp \
	Voxel/Graphics/Shader.cpp \
	\
	Voxel/Voxel.cpp \
	Voxel/VoxelTemplate.cpp \
	Voxel/VoxelOrientation.cpp \
	Voxel/VoxelEnums.cpp \
	Voxel/VoxelIndex.cpp \
	Voxel/Chunk.cpp \
	Voxel/ChunkNeighbours.cpp \
	Voxel/ChunkManager.cpp \
	\
	BoxEntity.cpp \
\
	GridCast/GridCast3D.cpp \
\
	Menus/Main.cpp \
	Menus/Pause.cpp \
	Menus/Options.cpp \
	Menus/Debug.cpp \
	Menus/Inventory.cpp \
	Menus/InventorySlot.cpp \
	Inventory/ItemBase.cpp \
	Inventory/ItemVoxel.cpp \
\
	main.cpp \

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

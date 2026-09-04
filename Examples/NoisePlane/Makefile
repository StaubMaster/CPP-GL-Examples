
NAME := NoisePlane.exe
FANCY_NAME := NoisePlane

################################################################

FILES := \
	Texture/FileMap.cpp \
	Texture/FileIndex.cpp \
\
	3D/Voxel.cpp \
	3D/Voxel/Pallet.cpp \
	3D/Voxel/Pallet/Map.cpp \
	3D/Voxel/Pallet/Geometry.cpp \
	3D/Voxel/Pallet/Geometry/Map.cpp \
	3D/Voxel/Pallet/Geometry/Parser.cpp \
	3D/Voxel/Pallet/Geometry/U.cpp \
	3D/Voxel/Pallet/Geometry/F.cpp \
\
	3D/Voxel/Pallet/Geometry/Graphics/ShaderLayout.cpp \
	3D/Voxel/Pallet/Geometry/Graphics/U/Data.cpp \
	3D/Voxel/Pallet/Geometry/Graphics/U/Layout.cpp \
	3D/Voxel/Pallet/Geometry/Graphics/F/Data.cpp \
	3D/Voxel/Pallet/Geometry/Graphics/F/Layout.cpp \
\
	3D/Chunk.cpp \
	3D/Chunk/GraphicsData.cpp \
	3D/Chunk/Neighbours.cpp \
	3D/Chunk/Manager.cpp \
\
	3D/VoxelHit.cpp \
	3D/ChunkVoxelIndex.cpp \
	3D/Structure.cpp \
\
	AuxThread/AuxThread1.cpp \
	AuxThread/AuxThread2.cpp \
	AuxThread/AuxThread3.cpp \
\
	BoxEntity3D.cpp \
\
	Menus/Main.cpp \
	Menus/Pause.cpp \
	Menus/Options.cpp \
	Menus/Debug.cpp \
\
	Item/ItemBase.cpp \
	Item/ItemVoxel.cpp \
	Item/ItemTool.cpp \
	Item/ItemContainer.cpp \
\
	Menus/Item/ItemSlotUI.cpp \
	Menus/Item/ItemContainerUI.cpp \
\
	ContextNoisePlane.cpp \
	Layout/Shader.cpp \
	Layout/Multiform.cpp \
	NewPolyHedraUI.cpp \
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

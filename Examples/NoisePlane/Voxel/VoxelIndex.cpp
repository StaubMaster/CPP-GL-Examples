#include "VoxelIndex.hpp"
#include "Chunk.hpp"



//bool VoxelIndex::Valid() const { return (ChunkPointer != nullptr); }



VoxelIndex::~VoxelIndex() { }
VoxelIndex::VoxelIndex()
//	: ChunkPointer(nullptr)
{ }



VoxelIndex::VoxelIndex(VectorI3 position)
{
	FromPosition(position);
}
VoxelIndex & VoxelIndex::operator=(VectorI3 position)
{
	FromPosition(position);
	return *this;
}



void VoxelIndex::FromPosition(VectorI3 position)
{
//	ChunkPointer = nullptr;
	Chunk = (VectorF3(position) / (float)CHUNK_VALUES_PER_SIDE).roundF(); // make intager division round down;
	Voxel = position - (Chunk * CHUNK_VALUES_PER_SIDE);
}
VectorI3 VoxelIndex::ToPosition() const
{
	return Voxel + (Chunk * CHUNK_VALUES_PER_SIDE);
}

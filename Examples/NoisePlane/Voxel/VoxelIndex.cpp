#include "VoxelIndex.hpp"
#include "Chunk.hpp"



bool VoxelIndex::Valid() const { return (ChunkMan != 0xFFFFFFFF); }



VoxelIndex::~VoxelIndex() { }
VoxelIndex::VoxelIndex()
	: ChunkMan(0xFFFFFFFF)
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
	ChunkMan = 0xFFFFFFFF;
	Chunk = (VectorF3(position) / (float)CHUNK_VALUES_PER_SIDE).roundF(); // make intager division round down;
	Voxel = position - (Chunk * CHUNK_VALUES_PER_SIDE);
}
VectorI3 VoxelIndex::ToPosition() const
{
	return Voxel + (Chunk * CHUNK_VALUES_PER_SIDE);
}

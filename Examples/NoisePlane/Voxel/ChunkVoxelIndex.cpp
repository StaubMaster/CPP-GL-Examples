#include "ChunkVoxelIndex.hpp"
#include "ValueType/VectorF3.hpp"
#include "Chunk.hpp"



ChunkVoxelIndex::~ChunkVoxelIndex() { }
ChunkVoxelIndex::ChunkVoxelIndex()
{ }



ChunkVoxelIndex::ChunkVoxelIndex(VectorI3 position)
{
	FromPosition(position);
}
ChunkVoxelIndex & ChunkVoxelIndex::operator=(VectorI3 position)
{
	FromPosition(position);
	return *this;
}



void ChunkVoxelIndex::FromPosition(VectorI3 position)
{
//	ChunkPointer = nullptr;
	Chunk = (VectorF3(position) / (float)CHUNK_VALUES_PER_SIDE).roundF(); // make intager division round down;
	Voxel = position - (Chunk * CHUNK_VALUES_PER_SIDE);
}
VectorI3 ChunkVoxelIndex::ToPosition() const
{
	return Voxel + (Chunk * CHUNK_VALUES_PER_SIDE);
}

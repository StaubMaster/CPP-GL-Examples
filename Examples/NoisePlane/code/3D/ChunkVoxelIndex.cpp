#include "ChunkVoxelIndex.hpp"
#include "ValueType/Vector/F3.hpp"
#include "Chunk.hpp"



ChunkVoxelIndex::ChunkVoxelIndex(const VectorI3 & position)
{
	FromPosition(position);
}
ChunkVoxelIndex & ChunkVoxelIndex::operator=(const VectorI3 & position)
{
	FromPosition(position);
	return *this;
}



void ChunkVoxelIndex::FromPosition(VectorI3 position)
{
//	ChunkPointer = nullptr;
	Chunk = ((position.ToF() / (float)CHUNK_VALUES_PER_SIDE).roundF()).ToI(); // make intager division round down;
	Voxel = (position - (Chunk * CHUNK_VALUES_PER_SIDE)).ToU();
}
VectorI3 ChunkVoxelIndex::ToPosition() const
{
	return Voxel.ToI() + (Chunk * CHUNK_VALUES_PER_SIDE);
}

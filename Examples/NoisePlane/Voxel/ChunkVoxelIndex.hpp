#ifndef  CHUNK_VOXEL_INDEX_HPP
# define CHUNK_VOXEL_INDEX_HPP

# include "ValueType/Vector/I3.hpp"
# include "ValueType/Vector/U3.hpp"

struct ChunkVoxelIndex
{
	VectorI3	Chunk;
	VectorU3	Voxel;

	~ChunkVoxelIndex();
	ChunkVoxelIndex();

	ChunkVoxelIndex(const ChunkVoxelIndex & other) = delete;
	ChunkVoxelIndex & operator=(const ChunkVoxelIndex & other) = delete;

	ChunkVoxelIndex(VectorI3 position);
	ChunkVoxelIndex & operator=(VectorI3 position);

	void		FromPosition(VectorI3 position);
	VectorI3	ToPosition() const;
};

#endif
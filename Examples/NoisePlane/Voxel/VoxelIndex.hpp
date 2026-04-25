#ifndef  VOXEL_INDEX_HPP
# define VOXEL_INDEX_HPP

# include "ValueType/VectorI3.hpp"
# include "ValueType/VectorU3.hpp"

struct VoxelIndex
{
	unsigned int	ChunkMan; // Chunk Index in Manager
	VectorI3		Chunk;
	VectorU3		Voxel;

	bool	Valid() const;

	~VoxelIndex();
	VoxelIndex();

	VoxelIndex(VectorI3 position);
	VoxelIndex & operator=(VectorI3 position);

	void		FromPosition(VectorI3 position);
	VectorI3	ToPosition() const;
};

#endif
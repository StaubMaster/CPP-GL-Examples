#ifndef  CHUNK_VOXEL_INDEX_HPP
# define CHUNK_VOXEL_INDEX_HPP

# include "ValueType/Vector/I3.hpp"
# include "ValueType/Vector/U3.hpp"

// 
/* Functions
	void	AxisInc()
	void	AxisDec()
	Index	AxisAdd()
	Index	AxisSub()
*/
struct ChunkVoxelIndex
{
	VectorI3	Chunk;
	VectorU3	Voxel;

	~ChunkVoxelIndex() = default;
	ChunkVoxelIndex() = default;
	ChunkVoxelIndex(const ChunkVoxelIndex & other) = default;
	ChunkVoxelIndex & operator=(const ChunkVoxelIndex & other) = default;

	ChunkVoxelIndex(const VectorI3 & position);
	ChunkVoxelIndex & operator=(const VectorI3 & position);

	void		FromPosition(VectorI3 position);
	VectorI3	ToPosition() const;
};

#endif
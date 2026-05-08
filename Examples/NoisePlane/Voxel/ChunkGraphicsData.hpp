#ifndef  CHUNK_GRAPHICS_DATA_HPP
# define CHUNK_GRAPHICS_DATA_HPP

# include "Graphics/Main/Data.hpp"
# include "VoxelEnums.hpp"

# include "Miscellaneous/Container/Array.hpp"
# include "BlockList.hpp"

struct VectorU3;
struct Voxel;
struct Chunk;

struct ChunkGraphicsData // ChunkGraphicsData
{
	BlockList<1024, VoxelGraphics::MainTriangle>	Data;
	Container::Array<VoxelGraphics::MainTriangle>	Array;

	void	Clear();
	void	Concatnate(VectorU3 u, const Voxel & voxel, AxisRel axis);
	void	Concatnate(VectorU3 u, const Voxel & voxel, AxisRel axis, const Chunk & chunk);
	void	Make(const Chunk & chunk);
	void	Done();
};

#endif
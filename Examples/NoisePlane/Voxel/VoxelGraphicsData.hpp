#ifndef  VOXEL_GRAPHICS_DATA_HPP
# define VOXEL_GRAPHICS_DATA_HPP

# include "Graphics/Main/Data.hpp"
# include "VoxelOrientation.hpp" // only for AxisRel

# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Container/Array.hpp"
# include "BlockList.hpp"

struct VectorU3;
struct Voxel;

struct VoxelAxisGraphicsData // VoxelAxisGraphicsData
{
	Container::Binary<VoxelGraphics::MainTriangle>	Data;

	// Clear()
	// Count()
	// operator[]
	// Insert()

	void	Done();
};
struct VoxelGraphicsData // VoxelGraphicsData
{
	VoxelAxisGraphicsData	Here;
	VoxelAxisGraphicsData	PrevX;
	VoxelAxisGraphicsData	PrevY;
	VoxelAxisGraphicsData	PrevZ;
	VoxelAxisGraphicsData	NextX;
	VoxelAxisGraphicsData	NextY;
	VoxelAxisGraphicsData	NextZ;

	void	Done();

	const VoxelAxisGraphicsData &	AxisData(AxisRel axis) const;
};
struct ChunkGraphicsData // ChunkGraphicsData
{
	BlockList<1024, VoxelGraphics::MainTriangle>	Data;
	Container::Array<VoxelGraphics::MainTriangle>	Array;

	void	Clear();
	void	Concatnate(VectorU3 u, const Voxel & voxel, AxisRel axis);
	void	Done();
};

#endif
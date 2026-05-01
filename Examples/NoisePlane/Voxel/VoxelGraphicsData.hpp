#ifndef  VOXEL_GRAPHICS_DATA_HPP
# define VOXEL_GRAPHICS_DATA_HPP

# include "Graphics/Voxel.hpp"
# include "VoxelOrientation.hpp" // only for AxisRel

# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Container/Array.hpp"
# include "BlockList.hpp"

struct VectorU3;
struct Voxel;

struct VoxelAxisGraphicsData // VoxelAxisData
{
	Container::Binary<VoxelGraphics::MainTriangle>	Data;

	// Count()
	// operator[]
	// Insert()
};
struct VoxelGraphicsData
{
	VoxelAxisGraphicsData		Here;
	VoxelAxisGraphicsData		PrevX;
	VoxelAxisGraphicsData		PrevY;
	VoxelAxisGraphicsData		PrevZ;
	VoxelAxisGraphicsData		NextX;
	VoxelAxisGraphicsData		NextY;
	VoxelAxisGraphicsData		NextZ;

	const VoxelAxisGraphicsData &	AxisData(AxisRel axis) const;
};
struct ChunkGraphicsData // ChunkData
{
	BlockList<1024, VoxelGraphics::MainTriangle>		Data;
	Container::Array<VoxelGraphics::MainTriangle>	Array;

	void	Clear();
	void	Concatnate(VectorU3 u, const Voxel & voxel, AxisRel axis);
	void	Done();
};

#endif
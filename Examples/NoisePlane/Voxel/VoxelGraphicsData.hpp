#ifndef  VOXEL_GRAPHICS_DATA_HPP
# define VOXEL_GRAPHICS_DATA_HPP

# include "Graphics/Main/Data.hpp"
# include "VoxelOrientation.hpp" // only for AxisRel

# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Container/Array.hpp"
# include "Miscellaneous/Container/BlockLinkedList.hpp"

struct VectorU3;
struct Voxel;

struct VoxelVertexGraphicsDataU
{
	VectorU3	Pos;
	VectorU3	Tex;
};
struct VoxelAxisGraphicsDataU
{
	VoxelVertexGraphicsDataU	Data[4];
};
struct VoxelGraphicsDataU
{
	VoxelAxisGraphicsDataU	PrevX;
	VoxelAxisGraphicsDataU	PrevY;
	VoxelAxisGraphicsDataU	PrevZ;
	VoxelAxisGraphicsDataU	NextX;
	VoxelAxisGraphicsDataU	NextY;
	VoxelAxisGraphicsDataU	NextZ;

//	const VoxelAxisGraphicsDataU &	AxisData(AxisRel axis) const;
};
struct VoxelAxisGraphicsDataF // VoxelAxisGraphicsData
{
	Container::Binary<VoxelGraphics::MainFaceF>	Data;

	// Clear()
	// Count()
	// operator[]
	// Insert()

	void	Done();
};
struct VoxelGraphicsDataF // VoxelGraphicsData
{
	VoxelAxisGraphicsDataF	Here;
	VoxelAxisGraphicsDataF	PrevX;
	VoxelAxisGraphicsDataF	PrevY;
	VoxelAxisGraphicsDataF	PrevZ;
	VoxelAxisGraphicsDataF	NextX;
	VoxelAxisGraphicsDataF	NextY;
	VoxelAxisGraphicsDataF	NextZ;

	void	Done();

//	const VoxelAxisGraphicsDataF &	AxisData(AxisRel axis) const;
};

#endif
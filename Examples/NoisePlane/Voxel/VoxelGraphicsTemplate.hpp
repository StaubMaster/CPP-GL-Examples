#ifndef  VOXEL_GRAPHICS_TEMPLATE_HPP
# define VOXEL_GRAPHICS_TEMPLATE_HPP

# include "Graphics/Voxel.hpp"
# include "VoxelOrientation.hpp"
# include "VoxelGraphicsData.hpp"

struct VoxelGraphicsTemplate
{
	static VoxelGraphicsTemplate	Cube;
	static VoxelGraphicsTemplate	Cylinder;
	static VoxelGraphicsTemplate	Slope;



	VoxelGraphicsData	Here;
	VoxelGraphicsData	PrevX;
	VoxelGraphicsData	PrevY;
	VoxelGraphicsData	PrevZ;
	VoxelGraphicsData	NextX;
	VoxelGraphicsData	NextY;
	VoxelGraphicsData	NextZ;

	const VoxelGraphicsData &	AxisData(AxisRel axis) const;

	bool	HidePrevX;
	bool	HidePrevY;
	bool	HidePrevZ;

	bool	HideNextX;
	bool	HideNextY;
	bool	HideNextZ;

	bool	Visible(AxisRel axis) const;

	AxisRel		OrientationAxis0;
	AxisRel		OrientationAxis1;

	VoxelOrientation	Orient(AxisRel placeAxis0, AxisRel placeAxis1) const;



	void	InitCube();
	void	InitCylinder();
	void	InitSlope();
};

#endif
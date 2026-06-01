#ifndef  VOXEL_GEOMETRY_PALLET_HPP
# define VOXEL_GEOMETRY_PALLET_HPP

# include "AxisOrientation.hpp"
# include "VoxelGraphicsData.hpp"

struct VoxelGeometryPallet
{
	static VoxelGeometryPallet	Cube;
	static VoxelGeometryPallet	Cylinder;
	static VoxelGeometryPallet	Slope;

	static VoxelGraphicsDataU	DataU;

	static void		Default();


	/* DataU
		the corners of the cube are allways the same
		only the texture alignment / texture changes
		VoxelGraphicsDataU
		{
			[6][4] Texture Coordinate
		}
		if something is allways a full cube, then it dosent need DataF
	*/
	VoxelGraphicsDataF			Data; // this is Graphics Data. this whole struct is general VoxelTypeTemplate

	const VoxelAxisGraphicsDataU &	AxisDataU(AxisRel axis) const;
	const VoxelAxisGraphicsDataF &	AxisDataF(AxisRel axis) const;

	bool	HidePrevX;
	bool	HidePrevY;
	bool	HidePrevZ;

	bool	HideNextX;
	bool	HideNextY;
	bool	HideNextZ;

	bool	Visible(AxisRel axis) const;

	AxisRel		OrientationAxis0;
	AxisRel		OrientationAxis1;

	AxisOrientation	Orient(AxisRel placeAxis0, AxisRel placeAxis1) const;



	void	InitCube();
	void	InitCylinder();
	void	InitSlope();
};

#endif
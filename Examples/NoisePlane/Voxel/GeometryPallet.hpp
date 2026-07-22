#ifndef  VOXEL_GEOMETRY_PALLET_HPP
# define VOXEL_GEOMETRY_PALLET_HPP

# include "Axis/Orientation.hpp"
# include "GeometryDataU.hpp"
# include "GeometryDataF.hpp"

struct VoxelGeometryPallet
{
	static VoxelGeometryPallet	GeometryCube;
	static VoxelGeometryPallet	GeometryCylinder;
	static VoxelGeometryPallet	GeometrySlope;

	static VoxelGeometryDataU::Cube	GraphicsDataU; // this is Graphics Data for a full Voxel
	// Textures are aligned to the Diagonal
	// should make another for "Prism" Cube
	// there the Belt Textures are aligned to the Bases

	static void		Default();

	// GraphicsDataF is allways the same, except not really
	bool						UseF;
	VoxelGeometryDataF::Full	GraphicsDataF; // this is Graphics Data. this whole struct is general VoxelTypeTemplate

	const VoxelGeometryDataU::Face &	AxisDataU(AxisRel axis) const;
	const VoxelGeometryDataF::Face &	AxisDataF(AxisRel axis) const;

	// Full Cube Dosent need these ?
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
	/*DefaultCube()
		Textures are oriented around the Diagonal
	*/
	/*PrismYCube()

	*/
	void	InitCylinder(); // CylinderY() PrismY8()
	void	InitSlope();
};

#endif
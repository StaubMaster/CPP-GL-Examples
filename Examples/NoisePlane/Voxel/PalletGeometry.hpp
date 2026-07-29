#ifndef  VOXEL_GEOMETRY_PALLET_HPP
# define VOXEL_GEOMETRY_PALLET_HPP

# include "Axis/Orientation.hpp"
# include "GeometryDataU.hpp"
# include "GeometryDataF.hpp"

struct VoxelPalletGeometry
{
	static VoxelPalletGeometry	Cube;
	static VoxelPalletGeometry	AxisStar;
	static VoxelPalletGeometry	PrismY8;
	static VoxelPalletGeometry	Slope;

	// Textures are aligned to the Diagonal
	// should make another for "Prism" Cube
	// there the Belt Textures are aligned to the Bases

	VoxelGeometryDataU::Cube	DataU;
	VoxelGeometryDataF::Full	DataF;

	bool	UseF_PrevX;
	bool	UseF_PrevY;
	bool	UseF_PrevZ;
	bool	UseF_NextX;
	bool	UseF_NextY;
	bool	UseF_NextZ;
	bool	IsAxisVisible(AxisRel axis) const;

	const VoxelGeometryDataU::Face &	AxisDataU(AxisRel axis) const;
	const VoxelGeometryDataF::Axis &	AxisDataF(AxisRel axis) const;

	AxisRel		OrientationAxis0;
	AxisRel		OrientationAxis1;

	AxisOrientation	Orient(AxisRel placeAxis0, AxisRel placeAxis1) const;



	void	InitU();

	void	InitF_Cube();
	/*DefaultCube()
		Textures are oriented around the Diagonal
	*/
	/*PrismYCube()
		bases are 180 degrees rotated from eachother
		belts are rotated so the Y axis of the Textures goes between the bases
		should all Y face the same way, or should every other be spun 180 degrees ?
	*/

	void	InitF_AxisStar();
	void	InitF_PrismY8();
	void	InitF_Slope();
};

#endif
#ifndef  VOXEL_PALLET_GEOMETRY_HPP
# define VOXEL_PALLET_GEOMETRY_HPP

# include "Axis/Orientation.hpp"
# include "3D/Voxel/Pallet/Geometry/U.hpp"
# include "3D/Voxel/Pallet/Geometry/F.hpp"

struct VoxelPalletGeometry
{
//	static VoxelPalletGeometry	CubeDiag;
//	static VoxelPalletGeometry	CubeAxisY;
//	static VoxelPalletGeometry	AxisStar;
//	static VoxelPalletGeometry	PrismY8;
//	static VoxelPalletGeometry	Slope;

	const char *	Name = nullptr;

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



	/*DefaultCube()
		Textures are oriented around the Diagonal
	*/
	/*PrismYCube()
		bases are 180 degrees rotated from eachother
		belts are rotated so the Y axis of the Textures goes between the bases
		should all Y face the same way, or should every other be spun 180 degrees ?
	*/

	void	InitU_CubeDiag();
	void	InitF_CubeDiag();

	void	InitU_CubeAxisY();
	void	InitF_CubeAxisY();

	void	InitF_AxisStar();
	void	InitF_PrismY8();

	void	InitF_Slope();

	// do all these with Files ?
};

#endif
#ifndef  VOXEL_PALLET_GEOMETRY_HPP
# define VOXEL_PALLET_GEOMETRY_HPP

# include "Axis/3D/Orientation.hpp"
# include "3D/Voxel/Pallet/Geometry/U.hpp"
# include "3D/Voxel/Pallet/Geometry/F.hpp"

# include <string>

struct VoxelPalletGeometry
{
//	static VoxelPalletGeometry	CubeDiag;
//	static VoxelPalletGeometry	CubeAxisY;
//	static VoxelPalletGeometry	AxisStar;
//	static VoxelPalletGeometry	PrismY8;
//	static VoxelPalletGeometry	Slope;

	std::string		Name;
	// instead of allways 6 Textures, use a Variable number of Textures
	// store how many this Geometry needs

	// rename UseF_ to DisplayNeighbour_
	bool	UseF_PrevX = true;
	bool	UseF_PrevY = true;
	bool	UseF_PrevZ = true;
	bool	UseF_NextX = true;
	bool	UseF_NextY = true;
	bool	UseF_NextZ = true;

	VoxelGeometryDataU::Cube	DataU;
	VoxelGeometryDataF::Full	DataF;

	bool									IsAxisVisible(Axis3D::Rel axis) const;
	const	VoxelGeometryDataU::Face &		AxisDataU(Axis3D::Rel axis) const;
	const	VoxelGeometryDataF::Axis &		AxisDataF(Axis3D::Rel axis) const;
			VoxelGeometryDataU::Face &		AxisDataU(Axis3D::Rel axis);
			VoxelGeometryDataF::Axis &		AxisDataF(Axis3D::Rel axis);

	/* in Geometry of Pallet ?
		Cube
			could have: no Orientation
			could be Prism: Orientation
		Cylinder
			allways Orientation ?
	*/
	Axis3D::Rel		OrientationAxis0;
	Axis3D::Rel		OrientationAxis1;

	Axis3D::Orientation		Orient(Axis3D::Rel placeAxis0, Axis3D::Rel placeAxis1) const;



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



	// these are all the same Geometry
	// but with different Texture Orientation
	// rename Axis3D::Orientation to Axis3DOrientation
	// make Axis2DOrientation
	// give each Texture an Orientation member ?
	// make Texture Orientation part of Pallet, not PalletGeometry
	void	InitF_PrismY12();
};

#endif
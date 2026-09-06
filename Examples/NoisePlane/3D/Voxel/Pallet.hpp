#ifndef  VOXEL_PALLET_HPP
# define VOXEL_PALLET_HPP

# include "FileInfo.hpp"

# include "Axis/3D/Orientation.hpp"
# include "Axis/2D/Orientation.hpp"

struct Voxel;
struct VoxelPalletGeometry;
class PolyHedra;

// All(all): same Texture on all sides
// PrismX(base, belt): base Texture and belt Texture
// PrismY(base, belt): base Texture and belt Texture
// PrismZ(base, belt): base Texture and belt Texture
// Axis(prevX, prevY, prevZ, nextX, nextY, nextZ): different Textures

// takes a different number of Textures (hardcode 6 for testing ?)
// have different Cubes for each ?
// have 6 TextureIndex for each Axis (for now)

// Cube Texture Coordinates go from 0 to 5
// use those as Index for actual TextureIndex

# include "Texture/FileIndex.hpp"

typedef unsigned short VoxelPalletIndex;

enum class VoxelMaterialType
{
	None,
	Dirt,
	Stone,
	Wood,
	Powder,
};

/* Grain
	Solid
		Stone
		Wood
	Rough
		Dirt
	Powder
		Sand
*/

/* Hardness
	Hard
		Stone
		Sand
	Soft
		Wood
		Dirt
*/

# include <string>

struct VoxelPallet
{
	VoxelPalletIndex				Index = 0xFFFF;

	std::string						Name;
	const VoxelPalletGeometry *		Geometry = nullptr;
	VoxelMaterialType				Material = VoxelMaterialType::None;

	TextureFileIndex		Textures[6]; // make this a Container::Binary<> ?
	Axis2D::Orientation		TextureOrientations[6];

	::PolyHedra *		PolyHedra = nullptr;



	~VoxelPallet() = default;
	VoxelPallet() = default;
	VoxelPallet(const VoxelPallet & other) = default;
	VoxelPallet & operator=(const VoxelPallet & other) = default;

	VoxelPallet(VoxelPalletIndex idx, std::string name, const VoxelPalletGeometry & geometry, VoxelMaterialType material);



	void	TextureAxis(
		FileInfo prevX, Axis2D::Orientation prevX_orientation,
		FileInfo prevY, Axis2D::Orientation prevY_orientation,
		FileInfo prevZ, Axis2D::Orientation prevZ_orientation,
		FileInfo nextX, Axis2D::Orientation nextX_orientation,
		FileInfo nextY, Axis2D::Orientation nextY_orientation,
		FileInfo nextZ, Axis2D::Orientation nextZ_orientation
	);
	void	TextureAxis(
		FileInfo prevX, FileInfo prevY, FileInfo prevZ,
		FileInfo nextX, FileInfo nextY, FileInfo nextZ
	);
	void	TextureAxis(
		FileInfo axisX, FileInfo axisY, FileInfo axisZ
	);
	void	TexturePrismY(FileInfo base, FileInfo belt);
	void	TextureAll(FileInfo tex);



	void	MakePolyHedra();

	Voxel	ToVoxel() const;
	Voxel	ToVoxel(Axis3D::Rel placeAxis0, Axis3D::Rel placeAxis1) const;
};

#endif
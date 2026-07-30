#ifndef  VOXEL_PALLET_HPP
# define VOXEL_PALLET_HPP

# include "FileInfo.hpp"

# include "Axis/Orientation.hpp"

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

# include "TextureFileIndex.hpp"

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

struct VoxelPallet
{
	VoxelPalletIndex				Index = 0xFFFF;

	const char *					Name = nullptr;
	const VoxelPalletGeometry *		Geometry = nullptr;
	VoxelMaterialType				Material = VoxelMaterialType::None;

	TextureFileIndex	Textures[6];
	::PolyHedra *		PolyHedra = nullptr;



	~VoxelPallet() = default;
	VoxelPallet() = default;
	VoxelPallet(const VoxelPallet & other) = default;
	VoxelPallet & operator=(const VoxelPallet & other) = default;

	VoxelPallet(VoxelPalletIndex idx, const char * name, const VoxelPalletGeometry & geometry, VoxelMaterialType material);



	TextureFileIndex	FindTextureFileIndex(int idx) const;



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
	Voxel	ToVoxel(AxisRel placeAxis0, AxisRel placeAxis1) const;
};

#endif
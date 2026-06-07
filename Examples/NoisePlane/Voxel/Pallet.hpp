#ifndef  VOXEL_PALLET_HPP
# define VOXEL_PALLET_HPP

# include "FileInfo.hpp"

# include "Axis/Orientation.hpp"

struct Voxel;
struct VoxelGeometryPallet;
struct VoxelAxisGraphicsData;
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

struct TextureFileIndex
{
	FileInfo		File;
	unsigned int	Index;
};

struct VoxelPallet
{
	const char *					Name;
	const VoxelGeometryPallet *		GeometryPallet;

	TextureFileIndex	Textures[6];
	::PolyHedra *		PolyHedra;
	unsigned int		Index;



	~VoxelPallet();
	VoxelPallet();
	VoxelPallet(const char * name, const VoxelGeometryPallet & geometry_template, unsigned int idx);

	VoxelPallet(const VoxelPallet & other);
	VoxelPallet & operator=(const VoxelPallet & other);



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

# include "Miscellaneous/Container/Binary.hpp"

class DirectoryInfo;
struct ChunkManager;
struct VoxelPalletMap
{
	static VoxelPalletMap	All;

	Container::Binary<VoxelPallet>	Data;

	// have a default to return if name is not found

	// use unsigned short instead of Pointer

	VoxelPallet &			operator[](unsigned short idx);
	const VoxelPallet &		operator[](unsigned short idx) const;

	VoxelPallet &			operator[](const char * name);
	const VoxelPallet &		operator[](const char * name) const;

	unsigned short			FindIndex(const char * name) const;
	unsigned short			FindIndex(const VoxelPallet * pallet) const;
	unsigned short			FindIndex(const VoxelPallet & pallet) const;

	void	Default(const DirectoryInfo & MediaDirectory);
	void	LoadTextures(ChunkManager & manager);
	void	MakePolyHedra();
};

#endif
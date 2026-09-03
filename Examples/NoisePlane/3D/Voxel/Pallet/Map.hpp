#ifndef  VOXEL_PALLET_MAP_HPP
# define VOXEL_PALLET_MAP_HPP

# include "Generics/Container/Binary.hpp"

struct VoxelPallet;
struct VoxelPalletGeometry;
struct ChunkManager;

struct TextureFileMap;

typedef unsigned short VoxelPalletIndex;
enum class VoxelMaterialType;

struct VoxelPalletMap
{
	static VoxelPalletMap	StaticMap;

	Container::Binary<VoxelPallet>	Data;

	VoxelPallet &			operator[](VoxelPalletIndex idx);
	const VoxelPallet &		operator[](VoxelPalletIndex idx) const;

	VoxelPallet &			operator[](const char * name);
	const VoxelPallet &		operator[](const char * name) const;

	VoxelPalletIndex		FindIndex(const char * name) const;
	VoxelPalletIndex		FindIndex(const VoxelPallet * pallet) const;
	VoxelPalletIndex		FindIndex(const VoxelPallet & pallet) const;

	VoxelPallet &	New(const char * name, const VoxelPalletGeometry & geometry, VoxelMaterialType material);

	void	TexturesAssign(TextureFileMap & tex_map);

	void	MakePolyHedras();
};

#endif
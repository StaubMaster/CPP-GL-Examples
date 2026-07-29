#ifndef  VOXEL_PALLET_MAP_HPP
# define VOXEL_PALLET_MAP_HPP

# include "Generics/Container/Binary.hpp"

struct VoxelPallet;
struct VoxelPalletGeometry;
class DirectoryInfo;
struct ChunkManager;

typedef unsigned short VoxelPalletIndex;

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

	VoxelPallet &	NewPallet(const char * name, const VoxelPalletGeometry & geometry);
	void	Default(const DirectoryInfo & MediaDirectory);
	void	TexturesAssign(ChunkManager & manager);
	void	MakePolyHedras();
};

#endif
#ifndef  VOXEL_PALLET_GEOMETRY_MAP_HPP
# define VOXEL_PALLET_GEOMETRY_MAP_HPP

# include "Generics/Container/Binary.hpp"

struct VoxelPalletGeometry;
typedef unsigned short VoxelPalletGeometryIndex;

# include <string>

struct VoxelPalletGeometryMap
{
	static VoxelPalletGeometryMap	StaticMap;

	Container::Binary<VoxelPalletGeometry>	Data;

	VoxelPalletGeometry &			operator[](VoxelPalletGeometryIndex idx);
	const VoxelPalletGeometry &		operator[](VoxelPalletGeometryIndex idx) const;

	VoxelPalletGeometry &			operator[](const char * name);
	const VoxelPalletGeometry &		operator[](const char * name) const;

	VoxelPalletGeometryIndex		FindIndex(const char * name) const;
	VoxelPalletGeometryIndex		FindIndex(const VoxelPalletGeometry * pallet) const;
	VoxelPalletGeometryIndex		FindIndex(const VoxelPalletGeometry & pallet) const;

	VoxelPalletGeometry &	New(const char * name);
	VoxelPalletGeometry &	New(std::string name);
};

#endif
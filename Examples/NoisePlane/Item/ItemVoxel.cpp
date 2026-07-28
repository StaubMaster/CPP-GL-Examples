#include "ItemVoxel.hpp"



ItemVoxel::ItemVoxel(const ::VoxelPallet & voxel_pallet)
	: ItemBase()
	, VoxelPallet(&voxel_pallet)
{ }
ItemVoxel::ItemVoxel(const ::VoxelPallet * voxel_pallet)
	: ItemBase()
	, VoxelPallet(voxel_pallet)
{ }

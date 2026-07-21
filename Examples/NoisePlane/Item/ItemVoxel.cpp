#include "ItemVoxel.hpp"
#include "ValueType/Vector/F2.hpp"



ItemVoxel::ItemVoxel(const ::VoxelPallet & voxel_pallet)
	: ItemBase()
	, VoxelPallet(&voxel_pallet)
{ }
ItemVoxel::ItemVoxel(const ::VoxelPallet * voxel_pallet)
	: ItemBase()
	, VoxelPallet(voxel_pallet)
{ }

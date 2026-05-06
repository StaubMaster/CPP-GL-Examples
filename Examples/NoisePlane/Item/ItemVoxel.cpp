#include "ItemVoxel.hpp"
#include "ValueType/VectorF2.hpp"



ItemVoxel::~ItemVoxel()
{ }
ItemVoxel::ItemVoxel()
	: ItemBase()
	, VoxelPallet(nullptr)
{ }
ItemVoxel::ItemVoxel(const ::VoxelPallet & voxel_pallet)
	: ItemBase()
	, VoxelPallet(&voxel_pallet)
{ }
ItemVoxel::ItemVoxel(const ::VoxelPallet * voxel_pallet)
	: ItemBase()
	, VoxelPallet(voxel_pallet)
{ }

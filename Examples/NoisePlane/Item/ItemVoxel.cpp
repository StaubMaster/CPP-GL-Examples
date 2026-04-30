#include "ItemVoxel.hpp"
#include "ValueType/VectorF2.hpp"



ItemVoxel::~ItemVoxel()
{ }
ItemVoxel::ItemVoxel()
	: ItemBase()
	, VoxelTemplate(nullptr)
{ }
ItemVoxel::ItemVoxel(const ::VoxelTemplate & voxel_template)
	: ItemBase()
	, VoxelTemplate(&voxel_template)
{ }
ItemVoxel::ItemVoxel(const ::VoxelTemplate * voxel_template)
	: ItemBase()
	, VoxelTemplate(voxel_template)
{ }

#ifndef  ITEM_VOXEL_HPP
# define ITEM_VOXEL_HPP

# include "ItemBase.hpp"

# include "Voxel/VoxelTemplate.hpp"

struct ItemVoxel : public ItemBase
{
	const ::VoxelTemplate *		VoxelTemplate;
	~ItemVoxel();
	ItemVoxel();
	ItemVoxel(const ::VoxelTemplate & voxel_template);
	ItemVoxel(const ::VoxelTemplate * voxel_template);
};

#endif
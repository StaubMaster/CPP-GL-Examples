#ifndef  ITEM_VOXEL_HPP
# define ITEM_VOXEL_HPP

# include "ItemBase.hpp"

# include "Voxel/VoxelPallet.hpp"

struct ItemVoxel : public ItemBase
{
	const ::VoxelPallet *		VoxelPallet;
	~ItemVoxel();
	ItemVoxel();
	ItemVoxel(const ::VoxelPallet & voxel_pallet);
	ItemVoxel(const ::VoxelPallet * voxel_pallet);
};

#endif
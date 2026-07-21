#ifndef  ITEM_VOXEL_HPP
# define ITEM_VOXEL_HPP

# include "ItemBase.hpp"

# include "Voxel/Pallet.hpp"

struct ItemVoxel : public ItemBase
{
	const ::VoxelPallet *	VoxelPallet = nullptr;
	unsigned int			Count = 0;
	~ItemVoxel() = default;
	ItemVoxel() = default;
	ItemVoxel(const ::VoxelPallet & voxel_pallet);
	ItemVoxel(const ::VoxelPallet * voxel_pallet);
};

#endif
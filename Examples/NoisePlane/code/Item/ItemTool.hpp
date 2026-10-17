#ifndef  ITEM_TOOL_HPP
# define ITEM_TOOL_HPP

# include "ItemBase.hpp"

# include "PolyHedra/PolyHedra.hpp"

# include "3D/Voxel/Pallet.hpp"

struct ItemTool : public ItemBase
{
	::PolyHedra *		Pallet = nullptr;

	VoxelMaterialType	Material = VoxelMaterialType::None;
	float				Multiplier = 1.0f;

	~ItemTool() = default;
	ItemTool() = default;
	ItemTool(::PolyHedra & pallet, VoxelMaterialType material, float multiplier);
	ItemTool(::PolyHedra * pallet, VoxelMaterialType material, float multiplier);
};

#endif
#include "ItemTool.hpp"



ItemTool::ItemTool(::PolyHedra & pallet, VoxelMaterialType material, float multiplier)
	: ItemBase()
	, Pallet(&pallet)
	, Material(material)
	, Multiplier(multiplier)
{ }
ItemTool::ItemTool(::PolyHedra * pallet, VoxelMaterialType material, float multiplier)
	: ItemBase()
	, Pallet(pallet)
	, Material(material)
	, Multiplier(multiplier)
{ }

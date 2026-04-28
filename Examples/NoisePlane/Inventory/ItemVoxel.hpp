#ifndef  ITEM_VOXEL_HPP
# define ITEM_VOXEL_HPP

// store the VoxelTemplate and a Count
// put VoxelTemplate Graphics Data into a Buffer
// make it spin ?
// use Instances for multiples ?
// keep all Items in Buffers at all times ?

// UI PolyHedra Manager ?
// like a regular PolyHedraManager but different Instance Data ?
// should I copy the ond PolyHedra Manager ?
// I would rather reuse the old one
// maybe Generalize ?
// I dont want to do eighter of those

// is there a Better way ?
// what I need is basically just the PolyHedra Manager with different Shader and Instances

// what do these Managers do ?
// MainValueType, MainData(MainValueType)
// InstValueType, InstData(InstValueType)

// MainValueType fills the Buffer
// InstValueType is a part of the Buffer

// Instance
//  Position (Pixels)
//  Rotation
//  Scale
//  implement Scale and this is just regular Trans3D ?
//  Scale should be the same, so just hardcode ?

// how to not mix up with old PolyHedra Manager ?
// allways MakeCurrent
// maybe make Object take Manager

# include "ItemBase.hpp"

# include "Voxel/VoxelTemplate.hpp"

# include "PolyHedra/Object.hpp"

struct ItemVoxel : public ItemBase
{
	::VoxelTemplate *	VoxelTemplate;
	::PolyHedraObject	PolyHedraObject;
	~ItemVoxel();
	ItemVoxel();
	void	Show(VectorF2 pos) override;
	void	Hide() override;
};

#endif
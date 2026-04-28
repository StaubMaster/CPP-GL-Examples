#include "ItemVoxel.hpp"
#include "ValueType/VectorF2.hpp"



ItemVoxel::~ItemVoxel()
{ }
ItemVoxel::ItemVoxel()
	: ItemBase()
	, VoxelTemplate(nullptr)
{ }



void ItemVoxel::Show(VectorF2 pos)
{
	if (VoxelTemplate != nullptr && VoxelTemplate -> PolyHedra != nullptr)
	{
		PolyHedraObject.Create(VoxelTemplate -> PolyHedra);
		PolyHedraObject.Trans().Position.X = pos.X;
		PolyHedraObject.Trans().Position.Y = pos.Y;
		PolyHedraObject.Trans().Rotation.X1 = Angle::Degrees(45);
		PolyHedraObject.Trans().Rotation.Y2 = Angle::Degrees(45);
	}
}
void ItemVoxel::Hide()
{
	PolyHedraObject.Delete();
}

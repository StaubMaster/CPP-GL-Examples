#include "Voxel.hpp"
#include "Voxel/Pallet.hpp"
#include "Voxel/PalletMap.hpp"
#include "Voxel/PalletGeometry.hpp"

#include "ValueType/Vector/U3.hpp"



bool Voxel::IsEmpty() const
{
	return (Pallet == 0xFFFF);
}
void Voxel::MakeEmpty()
{
	Pallet = 0xFFFF;
}
const VoxelPallet & Voxel::ToPallet() const
{
	return VoxelPalletMap::StaticMap[Pallet];
}
void Voxel::MakePallet(const VoxelPallet & pallet)
{
	Pallet = pallet.Index;
}



bool Voxel::IsAxisVisible(AxisRel axis) const
{
	if (IsEmpty()) { return true; }
	const VoxelPallet & pallet = ToPallet();
	if (pallet.Geometry == nullptr) { return true; }
	return pallet.Geometry -> IsAxisVisible(Orientation.relative(axis));
}

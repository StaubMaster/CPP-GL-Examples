#include "3D/Voxel.hpp"
#include "3D/Voxel/Pallet.hpp"
#include "3D/Voxel/Pallet/Map.hpp"
#include "3D/Voxel/Pallet/Geometry.hpp"

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

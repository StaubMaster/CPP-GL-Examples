#include "Voxel.hpp"
#include "VoxelPallet.hpp"
#include "VoxelGeometryPallet.hpp"
#include "ValueType/Vector/U3.hpp"



bool Voxel::IsEmpty() const { return (Pallet == 0xFFFF); }
bool Voxel::Visible(AxisRel axis) const
{
	if (Pallet == 0xFFFF) { return true; }
	const VoxelPallet & pallet = VoxelPalletMap::All[Pallet];
	if (pallet.GeometryPallet == nullptr) { return true; }
	//return Pallet -> GeometryPallet -> Visible(Orientation.relative(axis));
	return pallet.GeometryPallet -> Visible(axis);
}



Voxel::~Voxel() { }
Voxel::Voxel()
	: Pallet(0xFFFF)
	, Orientation()
{ }

Voxel::Voxel(const Voxel & other)
	: Pallet(other.Pallet)
	, Orientation(other.Orientation)
{ }
Voxel & Voxel::operator=(const Voxel & other)
{
	Pallet = other.Pallet;
	Orientation = other.Orientation;
	return *this;
}

#include "Voxel.hpp"
#include "Voxel/Pallet.hpp"
#include "Voxel/GeometryPallet.hpp"

#include "ValueType/Vector/U3.hpp"



bool Voxel::IsEmpty() const { return (Pallet == 0xFFFF); }
bool Voxel::Visible(AxisRel axis) const
{
	if (IsEmpty()) { return true; }
	const VoxelPallet & pallet = VoxelPalletMap::All[Pallet];
	if (pallet.GeometryPallet == nullptr) { return true; }
	//return Pallet -> GeometryPallet -> Visible(Orientation.relative(axis));
	return pallet.GeometryPallet -> Visible(axis);
	//return false; (void)axis;
}



void Voxel::MakeEmpty()
{
	Pallet = 0xFFFF;
}
/*void Voxel::Make(const VoxelPallet & pallet)
{
	(void)pallet;
	//Pallet = pallet.
}*/



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

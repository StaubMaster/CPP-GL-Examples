#include "Voxel.hpp"
#include "VoxelPallet.hpp"
#include "VoxelGeometryPallet.hpp"
#include "ValueType/VectorU3.hpp"



bool Voxel::Visible(AxisRel axis) const
{
	if (Pallet == nullptr) { return true; }
	if (Pallet -> GeometryPallet == nullptr) { return true; }
	//return Pallet -> GeometryPallet -> Visible(Orientation.relative(axis));
	return Pallet -> GeometryPallet -> Visible(axis);
}



Voxel::~Voxel() { }
Voxel::Voxel()
	: Pallet(nullptr)
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

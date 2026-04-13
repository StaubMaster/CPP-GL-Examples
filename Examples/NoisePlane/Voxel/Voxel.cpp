#include "Voxel.hpp"
#include "ValueType/VectorU3.hpp"



Voxel::~Voxel() { }
Voxel::Voxel()
	: Value(0.0f)
{ }

Voxel::Voxel(const Voxel & other)
	: Value(other.Value)
{ }
Voxel & Voxel::operator=(const Voxel & other)
{
	Value = other.Value;
	return *this;
}



bool Voxel::IsSolid() const
{
	return (Value != 0.0f);
}



static ColorF4 UndexToColor(VectorU3 u)
{
	ColorF4 col;
	col.R = (u.X % 2);
	col.G = (u.Y % 2);
	col.B = (u.Z % 2);
	return col;
}

VoxelGraphics::VoxelData Voxel::ToGraphics(VectorU3 u) const
{
	VoxelGraphics::VoxelData data;

	data.Data[0b000].Pos = Point3D(u.X + 0, u.Y + 0, u.Z + 0) * VOXEL_SCALE;
	data.Data[0b001].Pos = Point3D(u.X + 1, u.Y + 0, u.Z + 0) * VOXEL_SCALE;
	data.Data[0b010].Pos = Point3D(u.X + 0, u.Y + 1, u.Z + 0) * VOXEL_SCALE;
	data.Data[0b011].Pos = Point3D(u.X + 1, u.Y + 1, u.Z + 0) * VOXEL_SCALE;
	data.Data[0b100].Pos = Point3D(u.X + 0, u.Y + 0, u.Z + 1) * VOXEL_SCALE;
	data.Data[0b101].Pos = Point3D(u.X + 1, u.Y + 0, u.Z + 1) * VOXEL_SCALE;
	data.Data[0b110].Pos = Point3D(u.X + 0, u.Y + 1, u.Z + 1) * VOXEL_SCALE;
	data.Data[0b111].Pos = Point3D(u.X + 1, u.Y + 1, u.Z + 1) * VOXEL_SCALE;

	ColorF4 col = UndexToColor(u);
	for (unsigned int i = 0; i < 8; i++) { data.Data[i].Col = col; }

	return data;
}

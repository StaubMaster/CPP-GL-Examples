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



VoxelGraphics::VoxelCube Voxel::ToGraphics(VectorU3 u) const
{
	Point3D pos[8];
	pos[0b000] = Point3D(u.X + 0, u.Y + 0, u.Z + 0);
	pos[0b001] = Point3D(u.X + 1, u.Y + 0, u.Z + 0);
	pos[0b010] = Point3D(u.X + 0, u.Y + 1, u.Z + 0);
	pos[0b011] = Point3D(u.X + 1, u.Y + 1, u.Z + 0);
	pos[0b100] = Point3D(u.X + 0, u.Y + 0, u.Z + 1);
	pos[0b101] = Point3D(u.X + 1, u.Y + 0, u.Z + 1);
	pos[0b110] = Point3D(u.X + 0, u.Y + 1, u.Z + 1);
	pos[0b111] = Point3D(u.X + 1, u.Y + 1, u.Z + 1);
//	pos[0b111] = u + VectorU3(1, 1, 1);

	float tex = Value - 1;

	VoxelGraphics::VoxelCube data;

//	data.PrevX.Corn[0b00] = MainData(pos[0b000], Point3D(0.00f, 0.0f, tex));
	data.PrevX.Corn[0b00].Pos = pos[0b000]; data.PrevX.Corn[0b00].Tex = Point3D(0.00f, 0.0f, tex);
	data.PrevX.Corn[0b01].Pos = pos[0b010]; data.PrevX.Corn[0b01].Tex = Point3D(0.25f, 0.0f, tex);
	data.PrevX.Corn[0b10].Pos = pos[0b100]; data.PrevX.Corn[0b10].Tex = Point3D(0.00f, 0.5f, tex);
	data.PrevX.Corn[0b11].Pos = pos[0b110]; data.PrevX.Corn[0b11].Tex = Point3D(0.25f, 0.5f, tex);

	data.PrevY.Corn[0b00].Pos = pos[0b000]; data.PrevY.Corn[0b00].Tex = Point3D(0.25f, 0.0f, tex);
	data.PrevY.Corn[0b01].Pos = pos[0b100]; data.PrevY.Corn[0b01].Tex = Point3D(0.50f, 0.0f, tex);
	data.PrevY.Corn[0b10].Pos = pos[0b001]; data.PrevY.Corn[0b10].Tex = Point3D(0.25f, 0.5f, tex);
	data.PrevY.Corn[0b11].Pos = pos[0b101]; data.PrevY.Corn[0b11].Tex = Point3D(0.50f, 0.5f, tex);

	data.PrevZ.Corn[0b00].Pos = pos[0b000]; data.PrevZ.Corn[0b00].Tex = Point3D(0.50f, 0.0f, tex);
	data.PrevZ.Corn[0b01].Pos = pos[0b001]; data.PrevZ.Corn[0b01].Tex = Point3D(0.75f, 0.0f, tex);
	data.PrevZ.Corn[0b10].Pos = pos[0b010]; data.PrevZ.Corn[0b10].Tex = Point3D(0.50f, 0.5f, tex);
	data.PrevZ.Corn[0b11].Pos = pos[0b011]; data.PrevZ.Corn[0b11].Tex = Point3D(0.75f, 0.5f, tex);

	data.NextX.Corn[0b00].Pos = pos[0b001]; data.NextX.Corn[0b00].Tex = Point3D(0.00f, 0.5f, tex);
	data.NextX.Corn[0b10].Pos = pos[0b011]; data.NextX.Corn[0b01].Tex = Point3D(0.00f, 1.0f, tex);
	data.NextX.Corn[0b01].Pos = pos[0b101]; data.NextX.Corn[0b10].Tex = Point3D(0.25f, 0.5f, tex);
	data.NextX.Corn[0b11].Pos = pos[0b111]; data.NextX.Corn[0b11].Tex = Point3D(0.25f, 1.0f, tex);

	data.NextY.Corn[0b00].Pos = pos[0b010]; data.NextY.Corn[0b00].Tex = Point3D(0.25f, 0.5f, tex);
	data.NextY.Corn[0b10].Pos = pos[0b110]; data.NextY.Corn[0b01].Tex = Point3D(0.25f, 1.0f, tex);
	data.NextY.Corn[0b01].Pos = pos[0b011]; data.NextY.Corn[0b10].Tex = Point3D(0.50f, 0.5f, tex);
	data.NextY.Corn[0b11].Pos = pos[0b111]; data.NextY.Corn[0b11].Tex = Point3D(0.50f, 1.0f, tex);

	data.NextZ.Corn[0b00].Pos = pos[0b100]; data.NextZ.Corn[0b00].Tex = Point3D(0.50f, 0.5f, tex);
	data.NextZ.Corn[0b10].Pos = pos[0b101]; data.NextZ.Corn[0b01].Tex = Point3D(0.50f, 1.0f, tex);
	data.NextZ.Corn[0b01].Pos = pos[0b110]; data.NextZ.Corn[0b10].Tex = Point3D(0.75f, 0.5f, tex);
	data.NextZ.Corn[0b11].Pos = pos[0b111]; data.NextZ.Corn[0b11].Tex = Point3D(0.75f, 1.0f, tex);

	return data;
}

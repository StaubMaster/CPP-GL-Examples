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
	pos[0b000] = Point3D(u.X + 0, u.Y + 0, u.Z + 0) * VOXEL_SCALE;
	pos[0b001] = Point3D(u.X + 1, u.Y + 0, u.Z + 0) * VOXEL_SCALE;
	pos[0b010] = Point3D(u.X + 0, u.Y + 1, u.Z + 0) * VOXEL_SCALE;
	pos[0b011] = Point3D(u.X + 1, u.Y + 1, u.Z + 0) * VOXEL_SCALE;
	pos[0b100] = Point3D(u.X + 0, u.Y + 0, u.Z + 1) * VOXEL_SCALE;
	pos[0b101] = Point3D(u.X + 1, u.Y + 0, u.Z + 1) * VOXEL_SCALE;
	pos[0b110] = Point3D(u.X + 0, u.Y + 1, u.Z + 1) * VOXEL_SCALE;
	pos[0b111] = Point3D(u.X + 1, u.Y + 1, u.Z + 1) * VOXEL_SCALE;

	float tex = Value - 1;

	VoxelGraphics::VoxelCube data;

	data.Face[0].Corn[0b00].Pos = pos[0b000]; data.Face[0].Corn[0b00].Tex = Point3D(0.00f, 0.0f, tex);
	data.Face[0].Corn[0b01].Pos = pos[0b010]; data.Face[0].Corn[0b01].Tex = Point3D(0.25f, 0.0f, tex);
	data.Face[0].Corn[0b10].Pos = pos[0b100]; data.Face[0].Corn[0b10].Tex = Point3D(0.00f, 0.5f, tex);
	data.Face[0].Corn[0b11].Pos = pos[0b110]; data.Face[0].Corn[0b11].Tex = Point3D(0.25f, 0.5f, tex);

	data.Face[1].Corn[0b00].Pos = pos[0b000]; data.Face[1].Corn[0b00].Tex = Point3D(0.25f, 0.0f, tex);
	data.Face[1].Corn[0b01].Pos = pos[0b100]; data.Face[1].Corn[0b01].Tex = Point3D(0.50f, 0.0f, tex);
	data.Face[1].Corn[0b10].Pos = pos[0b001]; data.Face[1].Corn[0b10].Tex = Point3D(0.25f, 0.5f, tex);
	data.Face[1].Corn[0b11].Pos = pos[0b101]; data.Face[1].Corn[0b11].Tex = Point3D(0.50f, 0.5f, tex);

	data.Face[2].Corn[0b00].Pos = pos[0b000]; data.Face[2].Corn[0b00].Tex = Point3D(0.50f, 0.0f, tex);
	data.Face[2].Corn[0b01].Pos = pos[0b001]; data.Face[2].Corn[0b01].Tex = Point3D(0.75f, 0.0f, tex);
	data.Face[2].Corn[0b10].Pos = pos[0b010]; data.Face[2].Corn[0b10].Tex = Point3D(0.50f, 0.5f, tex);
	data.Face[2].Corn[0b11].Pos = pos[0b011]; data.Face[2].Corn[0b11].Tex = Point3D(0.75f, 0.5f, tex);

	data.Face[3].Corn[0b00].Pos = pos[0b001]; data.Face[3].Corn[0b00].Tex = Point3D(0.00f, 0.5f, tex);
	data.Face[3].Corn[0b10].Pos = pos[0b011]; data.Face[3].Corn[0b01].Tex = Point3D(0.00f, 1.0f, tex);
	data.Face[3].Corn[0b01].Pos = pos[0b101]; data.Face[3].Corn[0b10].Tex = Point3D(0.25f, 0.5f, tex);
	data.Face[3].Corn[0b11].Pos = pos[0b111]; data.Face[3].Corn[0b11].Tex = Point3D(0.25f, 1.0f, tex);

	data.Face[4].Corn[0b00].Pos = pos[0b010]; data.Face[4].Corn[0b00].Tex = Point3D(0.25f, 0.5f, tex);
	data.Face[4].Corn[0b10].Pos = pos[0b110]; data.Face[4].Corn[0b01].Tex = Point3D(0.25f, 1.0f, tex);
	data.Face[4].Corn[0b01].Pos = pos[0b011]; data.Face[4].Corn[0b10].Tex = Point3D(0.50f, 0.5f, tex);
	data.Face[4].Corn[0b11].Pos = pos[0b111]; data.Face[4].Corn[0b11].Tex = Point3D(0.50f, 1.0f, tex);

	data.Face[5].Corn[0b00].Pos = pos[0b100]; data.Face[5].Corn[0b00].Tex = Point3D(0.50f, 0.5f, tex);
	data.Face[5].Corn[0b10].Pos = pos[0b101]; data.Face[5].Corn[0b01].Tex = Point3D(0.50f, 1.0f, tex);
	data.Face[5].Corn[0b01].Pos = pos[0b110]; data.Face[5].Corn[0b10].Tex = Point3D(0.75f, 0.5f, tex);
	data.Face[5].Corn[0b11].Pos = pos[0b111]; data.Face[5].Corn[0b11].Tex = Point3D(0.75f, 1.0f, tex);

	return data;
}

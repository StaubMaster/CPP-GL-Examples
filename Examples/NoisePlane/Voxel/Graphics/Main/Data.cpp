#include "Data.hpp"



VoxelGraphics::MainData::~MainData() { }
VoxelGraphics::MainData::MainData()
	: Pos()
	, Tex()
	, Normal()
{ }

VoxelGraphics::MainData::MainData(const MainData & other)
	: Pos(other.Pos)
	, Tex(other.Tex)
	, Normal(other.Normal)
{ }
VoxelGraphics::MainData & VoxelGraphics::MainData::operator=(const MainData & other)
{
	Pos = other.Pos;
	Tex = other.Tex;
	Normal = other.Normal;
	return *this;
}

VoxelGraphics::MainData::MainData(VectorF3 pos, VectorF3 tex)
	: Pos(pos)
	, Tex(tex)
	, Normal()
{ }





VoxelGraphics::MainTriangle::~MainTriangle() { }
VoxelGraphics::MainTriangle::MainTriangle()
{ }

VoxelGraphics::MainTriangle::MainTriangle(const MainTriangle & other)
	: Corners{
		other.Corners[0],
		other.Corners[1],
		other.Corners[2],
	}
{ }
VoxelGraphics::MainTriangle & VoxelGraphics::MainTriangle::operator=(const MainTriangle & other)
{
	Corners[0] = other.Corners[0];
	Corners[1] = other.Corners[1];
	Corners[2] = other.Corners[2];
	return *this;
}



void VoxelGraphics::MainTriangle::CalcNormal()
{
	VectorF3 n = VectorF3::cross(Corners[1].Pos - Corners[0].Pos, Corners[2].Pos - Corners[0].Pos);
	Corners[0].Normal = n;
	Corners[1].Normal = n;
	Corners[2].Normal = n;
}

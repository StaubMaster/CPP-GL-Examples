#include "Data.hpp"



VoxelGraphics::MainData::~MainData() { }
VoxelGraphics::MainData::MainData()
	: Pos()
	, Tex()
{ }

VoxelGraphics::MainData::MainData(const MainData & other)
	: Pos(other.Pos)
	, Tex(other.Tex)
{ }
VoxelGraphics::MainData & VoxelGraphics::MainData::operator=(const MainData & other)
{
	Pos = other.Pos;
	Tex = other.Tex;
	return *this;
}

VoxelGraphics::MainData::MainData(VectorF3 pos, VectorF3 tex)
	: Pos(pos)
	, Tex(tex)
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

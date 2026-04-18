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

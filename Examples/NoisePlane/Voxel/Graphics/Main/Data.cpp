#include "Data.hpp"



VoxelGraphics::MainDataF::~MainDataF() { }
VoxelGraphics::MainDataF::MainDataF()
	: Pos()
	, Tex()
	, Normal()
{ }

VoxelGraphics::MainDataF::MainDataF(const MainDataF & other)
	: Pos(other.Pos)
	, Tex(other.Tex)
	, Normal(other.Normal)
{ }
VoxelGraphics::MainDataF & VoxelGraphics::MainDataF::operator=(const MainDataF & other)
{
	Pos = other.Pos;
	Tex = other.Tex;
	Normal = other.Normal;
	return *this;
}

VoxelGraphics::MainDataF::MainDataF(VectorF3 pos, VectorF3 tex)
	: Pos(pos)
	, Tex(tex)
	, Normal()
{ }





VoxelGraphics::MainFaceF::~MainFaceF() { }
VoxelGraphics::MainFaceF::MainFaceF()
{ }

VoxelGraphics::MainFaceF::MainFaceF(const MainFaceF & other)
	: Vertexes{
		other.Vertexes[0],
		other.Vertexes[1],
		other.Vertexes[2],
	}
{ }
VoxelGraphics::MainFaceF & VoxelGraphics::MainFaceF::operator=(const MainFaceF & other)
{
	Vertexes[0] = other.Vertexes[0];
	Vertexes[1] = other.Vertexes[1];
	Vertexes[2] = other.Vertexes[2];
	return *this;
}



void VoxelGraphics::MainFaceF::CalcNormal()
{
	VectorF3 n = VectorF3::cross(Vertexes[1].Pos - Vertexes[0].Pos, Vertexes[2].Pos - Vertexes[0].Pos);
	Vertexes[0].Normal = n;
	Vertexes[1].Normal = n;
	Vertexes[2].Normal = n;
}





VoxelGraphics::MainDataU::~MainDataU() { }
VoxelGraphics::MainDataU::MainDataU()
	: Value(0)
{ }

VoxelGraphics::MainDataU::MainDataU(const MainDataU & other)
	: Value(other.Value)
{ }
VoxelGraphics::MainDataU & VoxelGraphics::MainDataU::operator=(const MainDataU & other)
{
	Value = other.Value;
	return *this;
}

VoxelGraphics::MainDataU::MainDataU(VectorU3 pos, VectorU3 tex, AxisRel axis)
{
	(void)pos;
	(void)tex;
	(void)axis;
}





VoxelGraphics::MainFaceU::~MainFaceU() { }
VoxelGraphics::MainFaceU::MainFaceU()
{ }

VoxelGraphics::MainFaceU::MainFaceU(const MainFaceU & other)
	: Vertexes{
		other.Vertexes[0],
		other.Vertexes[1],
		other.Vertexes[2],
		other.Vertexes[3],
		other.Vertexes[4],
		other.Vertexes[5],
	}
{ }
VoxelGraphics::MainFaceU & VoxelGraphics::MainFaceU::operator=(const MainFaceU & other)
{
	Vertexes[0] = other.Vertexes[0];
	Vertexes[1] = other.Vertexes[1];
	Vertexes[2] = other.Vertexes[2];
	Vertexes[3] = other.Vertexes[3];
	Vertexes[4] = other.Vertexes[4];
	Vertexes[5] = other.Vertexes[5];
	return *this;
}

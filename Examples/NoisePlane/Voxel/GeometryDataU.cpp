#include "GeometryDataU.hpp"

#include "ValueType/Box/U2.hpp"



void VoxelGeometryDataU::Face::Quad0(VectorU3 p00, VectorU3 p01, VectorU3 p10, VectorU3 p11, BoxU2 box, unsigned int tex)
{
	Vertexes[0b00].Pos = p00;
	Vertexes[0b01].Pos = p10;
	Vertexes[0b10].Pos = p01;
	Vertexes[0b11].Pos = p11;

	Vertexes[0b00].Tex = VectorU2(box.Min.X, box.Min.Y);
	Vertexes[0b01].Tex = VectorU2(box.Min.X, box.Max.Y);
	Vertexes[0b10].Tex = VectorU2(box.Max.X, box.Min.Y);
	Vertexes[0b11].Tex = VectorU2(box.Max.X, box.Max.Y);

	Vertexes[0b00].Idx = tex;
	Vertexes[0b01].Idx = tex;
	Vertexes[0b10].Idx = tex;
	Vertexes[0b11].Idx = tex;
}
void VoxelGeometryDataU::Face::Quad1(VectorU3 p00, VectorU3 p01, VectorU3 p10, VectorU3 p11, BoxU2 box, unsigned int tex)
{
	Vertexes[0b00].Pos = p00;
	Vertexes[0b01].Pos = p10;
	Vertexes[0b10].Pos = p01;
	Vertexes[0b11].Pos = p11;

	Vertexes[0b00].Tex = VectorU2(box.Min.X, box.Min.Y);
	Vertexes[0b01].Tex = VectorU2(box.Max.X, box.Min.Y);
	Vertexes[0b10].Tex = VectorU2(box.Min.X, box.Max.Y);
	Vertexes[0b11].Tex = VectorU2(box.Max.X, box.Max.Y);

	Vertexes[0b00].Idx = tex;
	Vertexes[0b01].Idx = tex;
	Vertexes[0b10].Idx = tex;
	Vertexes[0b11].Idx = tex;
}

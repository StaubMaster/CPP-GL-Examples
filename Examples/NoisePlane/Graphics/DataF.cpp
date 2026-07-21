#include "DataF.hpp"



VoxelGraphicsDataF::Vertex::Vertex(VectorF3 pos, VectorF3 tex)
	: Pos(pos)
	, Tex(tex)
	, Normal()
{ }



void VoxelGraphicsDataF::Face::CalcNormal()
{
	VectorF3 n = VectorF3::cross(Vertexes[1].Pos - Vertexes[0].Pos, Vertexes[2].Pos - Vertexes[0].Pos);
	Vertexes[0].Normal = n;
	Vertexes[1].Normal = n;
	Vertexes[2].Normal = n;
}

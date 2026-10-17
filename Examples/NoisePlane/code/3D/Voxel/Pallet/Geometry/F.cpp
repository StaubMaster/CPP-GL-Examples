#include "3D/Voxel/Pallet/Geometry/F.hpp"

#include "ValueType/Box/F2.hpp"



VoxelGeometryDataF::Vertex::Vertex(VectorF3 pos, VectorF2 tex)
	: Pos(pos)
	, Tex(tex)
{ }



void VoxelGeometryDataF::Face::CalcNormal()
{
	Normal = VectorF3::cross(Vertexes[1].Pos - Vertexes[0].Pos, Vertexes[2].Pos - Vertexes[0].Pos);
}



void VoxelGeometryDataF::Axis::Tri0(VectorF3 p0, VectorF3 p1, VectorF3 p2, VectorF2 t0, VectorF2 t1, VectorF2 t2, unsigned int tex)
{
	Face face;
	face.Tex = tex;
	face.Vertexes[0] = Vertex(p0, t0);
	face.Vertexes[1] = Vertex(p1, t1);
	face.Vertexes[2] = Vertex(p2, t2);
	Data.Insert(face);
}
void VoxelGeometryDataF::Axis::Tri1(VectorF3 p0, VectorF3 p1, VectorF3 p2, VectorF2 t0, VectorF2 t1, VectorF2 t2, unsigned int tex)
{
	Face face;
	face.Tex = tex;
	face.Vertexes[0] = Vertex(p0, t0);
	face.Vertexes[1] = Vertex(p2, t2);
	face.Vertexes[2] = Vertex(p1, t1);
	Data.Insert(face);
}

void VoxelGeometryDataF::Axis::Quad1(VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11, BoxF2 box, unsigned int tex)
{
	Face face;
	face.Tex = tex;
	face.Vertexes[0] = Vertex(p00, VectorF2(box.Min.X, box.Min.Y));
	face.Vertexes[1] = Vertex(p10, VectorF2(box.Min.X, box.Max.Y));
	face.Vertexes[2] = Vertex(p01, VectorF2(box.Max.X, box.Min.Y));
	Data.Insert(face);
	face.Vertexes[0] = Vertex(p01, VectorF2(box.Max.X, box.Min.Y));
	face.Vertexes[1] = Vertex(p10, VectorF2(box.Min.X, box.Max.Y));
	face.Vertexes[2] = Vertex(p11, VectorF2(box.Max.X, box.Max.Y));
	Data.Insert(face);
}
void VoxelGeometryDataF::Axis::Quad0(VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11, BoxF2 box, unsigned int tex)
{
	Face face;
	face.Tex = tex;
	face.Vertexes[0] = Vertex(p00, VectorF2(box.Min.X, box.Min.Y));
	face.Vertexes[1] = Vertex(p10, VectorF2(box.Max.X, box.Min.Y));
	face.Vertexes[2] = Vertex(p01, VectorF2(box.Min.X, box.Max.Y));
	Data.Insert(face);
	face.Vertexes[0] = Vertex(p01, VectorF2(box.Min.X, box.Max.Y));
	face.Vertexes[1] = Vertex(p10, VectorF2(box.Max.X, box.Min.Y));
	face.Vertexes[2] = Vertex(p11, VectorF2(box.Max.X, box.Max.Y));
	Data.Insert(face);
}

void VoxelGeometryDataF::Axis::Done()
{
	for (unsigned int i = 0; i < Data.Count(); i++)
	{
		Data[i].CalcNormal();
	}
}



void VoxelGeometryDataF::Full::Done()
{
	Here.Done();
	PrevX.Done();
	PrevY.Done();
	PrevZ.Done();
	NextX.Done();
	NextY.Done();
	NextZ.Done();
}

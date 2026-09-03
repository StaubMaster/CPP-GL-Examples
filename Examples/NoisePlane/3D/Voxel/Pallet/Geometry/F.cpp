#include "3D/Voxel/Pallet/Geometry/F.hpp"

#include "ValueType/Box/F2.hpp"



void VoxelGeometryDataF::Axis::Tri0(VectorF3 p0, VectorF3 p1, VectorF3 p2, VectorF2 t0, VectorF2 t1, VectorF2 t2, unsigned int tex)
{
	VoxelGraphicsDataF::Face face;
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p0, VectorF3(t0.X, t0.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p1, VectorF3(t1.X, t1.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p2, VectorF3(t2.X, t2.Y, tex));
	Data.Insert(face);
}
void VoxelGeometryDataF::Axis::Tri1(VectorF3 p0, VectorF3 p1, VectorF3 p2, VectorF2 t0, VectorF2 t1, VectorF2 t2, unsigned int tex)
{
	VoxelGraphicsDataF::Face face;
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p0, VectorF3(t0.X, t0.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p2, VectorF3(t2.X, t2.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p1, VectorF3(t1.X, t1.Y, tex));
	Data.Insert(face);
}

void VoxelGeometryDataF::Axis::Quad1(VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11, BoxF2 box, unsigned int tex)
{
	VoxelGraphicsDataF::Face face;
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p00, VectorF3(box.Min.X, box.Min.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p10, VectorF3(box.Min.X, box.Max.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p01, VectorF3(box.Max.X, box.Min.Y, tex));
	Data.Insert(face);
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p01, VectorF3(box.Max.X, box.Min.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p10, VectorF3(box.Min.X, box.Max.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p11, VectorF3(box.Max.X, box.Max.Y, tex));
	Data.Insert(face);
}
void VoxelGeometryDataF::Axis::Quad0(VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11, BoxF2 box, unsigned int tex)
{
	VoxelGraphicsDataF::Face face;
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p00, VectorF3(box.Min.X, box.Min.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p10, VectorF3(box.Max.X, box.Min.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p01, VectorF3(box.Min.X, box.Max.Y, tex));
	Data.Insert(face);
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p01, VectorF3(box.Min.X, box.Max.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p10, VectorF3(box.Max.X, box.Min.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p11, VectorF3(box.Max.X, box.Max.Y, tex));
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

#include "GeometryPallet.hpp"

#include "ValueType/Box/F2.hpp"
#include "ValueType/Box/U2.hpp"



VoxelGeometryPallet VoxelGeometryPallet::GeometryCube;
VoxelGeometryPallet VoxelGeometryPallet::GeometryCylinder;
VoxelGeometryPallet VoxelGeometryPallet::GeometrySlope;

VoxelGeometryDataU::Cube VoxelGeometryPallet::GraphicsDataU;



static void Quad0(VoxelGeometryDataU::Face & face_data, VectorU3 p00, VectorU3 p01, VectorU3 p10, VectorU3 p11, BoxU2 box, unsigned int tex)
{
	face_data.Data[0b00].Pos = p00;
	face_data.Data[0b01].Pos = p10;
	face_data.Data[0b10].Pos = p01;
	face_data.Data[0b11].Pos = p11;

	face_data.Data[0b00].Tex = VectorU3(box.Min.X, box.Min.Y, tex);
	face_data.Data[0b01].Tex = VectorU3(box.Min.X, box.Max.Y, tex);
	face_data.Data[0b10].Tex = VectorU3(box.Max.X, box.Min.Y, tex);
	face_data.Data[0b11].Tex = VectorU3(box.Max.X, box.Max.Y, tex);
}
static void Quad1(VoxelGeometryDataU::Face & face_data, VectorU3 p00, VectorU3 p01, VectorU3 p10, VectorU3 p11, BoxU2 box, unsigned int tex)
{
	face_data.Data[0b00].Pos = p00;
	face_data.Data[0b01].Pos = p10;
	face_data.Data[0b10].Pos = p01;
	face_data.Data[0b11].Pos = p11;

	face_data.Data[0b00].Tex = VectorU3(box.Min.X, box.Min.Y, tex);
	face_data.Data[0b01].Tex = VectorU3(box.Max.X, box.Min.Y, tex);
	face_data.Data[0b10].Tex = VectorU3(box.Min.X, box.Max.Y, tex);
	face_data.Data[0b11].Tex = VectorU3(box.Max.X, box.Max.Y, tex);
}

void VoxelGeometryPallet::Default()
{
	VectorU3 pos[8];

	pos[0b000] = VectorU3(0, 0, 0);
	pos[0b001] = VectorU3(1, 0, 0);
	pos[0b010] = VectorU3(0, 1, 0);
	pos[0b011] = VectorU3(1, 1, 0);
	pos[0b100] = VectorU3(0, 0, 1);
	pos[0b101] = VectorU3(1, 0, 1);
	pos[0b110] = VectorU3(0, 1, 1);
	pos[0b111] = VectorU3(1, 1, 1);

	Quad0(GraphicsDataU.PrevX, pos[0b000], pos[0b010], pos[0b100], pos[0b110], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 0);
	Quad0(GraphicsDataU.PrevY, pos[0b000], pos[0b100], pos[0b001], pos[0b101], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 1);
	Quad0(GraphicsDataU.PrevZ, pos[0b000], pos[0b001], pos[0b010], pos[0b011], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 2);

	Quad1(GraphicsDataU.NextX, pos[0b001], pos[0b101], pos[0b011], pos[0b111], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 3);
	Quad1(GraphicsDataU.NextY, pos[0b010], pos[0b011], pos[0b110], pos[0b111], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 4);
	Quad1(GraphicsDataU.NextZ, pos[0b100], pos[0b110], pos[0b101], pos[0b111], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 5);
}



const VoxelGeometryDataU::Face & VoxelGeometryPallet::AxisDataU(AxisRel axis) const
{
	switch (axis)
	{
		case AxisRel::PrevX: return GraphicsDataU.PrevX;
		case AxisRel::PrevY: return GraphicsDataU.PrevY;
		case AxisRel::PrevZ: return GraphicsDataU.PrevZ;
		case AxisRel::NextX: return GraphicsDataU.NextX;
		case AxisRel::NextY: return GraphicsDataU.NextY;
		case AxisRel::NextZ: return GraphicsDataU.NextZ;
		default: break;
	}
	throw "VoxelGeometryPallet::AxisDataU: Invalid axis\n";
}
const VoxelGeometryDataF::Face & VoxelGeometryPallet::AxisDataF(AxisRel axis) const
{
	switch (axis)
	{
		case AxisRel::PrevX: return GraphicsDataF.PrevX;
		case AxisRel::PrevY: return GraphicsDataF.PrevY;
		case AxisRel::PrevZ: return GraphicsDataF.PrevZ;
		case AxisRel::NextX: return GraphicsDataF.NextX;
		case AxisRel::NextY: return GraphicsDataF.NextY;
		case AxisRel::NextZ: return GraphicsDataF.NextZ;
		default: return GraphicsDataF.Here;
	}
}

bool VoxelGeometryPallet::Visible(AxisRel axis) const
{
	switch (axis)
	{
		case AxisRel::None: return false;
		case AxisRel::PrevX: return !HideNextX;
		case AxisRel::PrevY: return !HideNextY;
		case AxisRel::PrevZ: return !HideNextZ;
		case AxisRel::NextX: return !HidePrevX;
		case AxisRel::NextY: return !HidePrevY;
		case AxisRel::NextZ: return !HidePrevZ;
		case AxisRel::Here: return true;
		default: return false;
	}
}

AxisOrientation VoxelGeometryPallet::Orient(AxisRel placeAxis0, AxisRel placeAxis1) const
{
	AxisOrientation orient;
	orient.make(OrientationAxis0, placeAxis0, OrientationAxis1, placeAxis1);
	return orient;
}



static void Quad0(VoxelGeometryDataF::Face & face_data, VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11, BoxF2 box, float tex)
{
	VoxelGraphicsDataF::Face	face;
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p00, VectorF3(box.Min.X, box.Min.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p10, VectorF3(box.Min.X, box.Max.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p01, VectorF3(box.Max.X, box.Min.Y, tex));
	face_data.Data.Insert(face);
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p01, VectorF3(box.Max.X, box.Min.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p10, VectorF3(box.Min.X, box.Max.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p11, VectorF3(box.Max.X, box.Max.Y, tex));
	face_data.Data.Insert(face);
}
static void Quad1(VoxelGeometryDataF::Face & face_data, VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11, BoxF2 box, float tex)
{
	VoxelGraphicsDataF::Face	face;
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p00, VectorF3(box.Min.X, box.Min.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p10, VectorF3(box.Max.X, box.Min.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p01, VectorF3(box.Min.X, box.Max.Y, tex));
	face_data.Data.Insert(face);
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p01, VectorF3(box.Min.X, box.Max.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p10, VectorF3(box.Max.X, box.Min.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p11, VectorF3(box.Max.X, box.Max.Y, tex));
	face_data.Data.Insert(face);
}



// Textures are currently mapped onto a single Texture
// should be 6 Textures
// [0.00;0.25][0.0;0.5][tex] = [0;1][0;1][0]
// [0.25;0.50][0.0;0.5][tex] = [0;1][0;1][1]
// [0.50;0.75][0.0;0.5][tex] = [0;1][0;1][2]
// [0.00;0.25][0.5;1.0][tex] = [0;1][0;1][3]
// [0.25;0.50][0.5;1.0][tex] = [0;1][0;1][4]
// [0.50;0.75][0.5;1.0][tex] = [0;1][0;1][5]

void VoxelGeometryPallet::InitCube()
{
	HidePrevX = true;
	HidePrevY = true;
	HidePrevZ = true;

	HideNextX = true;
	HideNextY = true;
	HideNextZ = true;

	OrientationAxis0 = AxisRel::None;
	OrientationAxis1 = AxisRel::None;

	VectorF3 pos[8];

	pos[0b000] = VectorF3(0.0f, 0.0f, 0.0f);
	pos[0b001] = VectorF3(1.0f, 0.0f, 0.0f);
	pos[0b010] = VectorF3(0.0f, 1.0f, 0.0f);
	pos[0b011] = VectorF3(1.0f, 1.0f, 0.0f);
	pos[0b100] = VectorF3(0.0f, 0.0f, 1.0f);
	pos[0b101] = VectorF3(1.0f, 0.0f, 1.0f);
	pos[0b110] = VectorF3(0.0f, 1.0f, 1.0f);
	pos[0b111] = VectorF3(1.0f, 1.0f, 1.0f);

	Quad0(GraphicsDataF.PrevX, pos[0b000], pos[0b010], pos[0b100], pos[0b110], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 0);
	Quad0(GraphicsDataF.PrevY, pos[0b000], pos[0b100], pos[0b001], pos[0b101], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 1);
	Quad0(GraphicsDataF.PrevZ, pos[0b000], pos[0b001], pos[0b010], pos[0b011], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 2);

	Quad1(GraphicsDataF.NextX, pos[0b001], pos[0b101], pos[0b011], pos[0b111], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 3);
	Quad1(GraphicsDataF.NextY, pos[0b010], pos[0b011], pos[0b110], pos[0b111], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 4);
	Quad1(GraphicsDataF.NextZ, pos[0b100], pos[0b110], pos[0b101], pos[0b111], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 5);

	GraphicsDataF.Done();
}

void VoxelGeometryPallet::InitCylinder()
{
	HidePrevX = false;
	HidePrevY = false;
	HidePrevZ = false;

	HideNextX = false;
	HideNextY = false;
	HideNextZ = false;

	OrientationAxis0 = AxisRel::PrevY;
	OrientationAxis1 = AxisRel::None;

	float f___ = 0.3f;

	VectorF3 pos[16];

	pos[0x00] = VectorF3(0.0f + f___, 0.0f, 0.0f);
	pos[0x01] = VectorF3(1.0f - f___, 0.0f, 0.0f);
	pos[0x02] = VectorF3(1.0f, 0.0f, 0.0f + f___);
	pos[0x03] = VectorF3(1.0f, 0.0f, 1.0f - f___);
	pos[0x04] = VectorF3(1.0f - f___, 0.0f, 1.0f);
	pos[0x05] = VectorF3(0.0f + f___, 0.0f, 1.0f);
	pos[0x06] = VectorF3(0.0f, 0.0f, 1.0f - f___);
	pos[0x07] = VectorF3(0.0f, 0.0f, 0.0f + f___);

	pos[0x08] = VectorF3(0.0f + f___, 1.0f, 0.0f);
	pos[0x09] = VectorF3(1.0f - f___, 1.0f, 0.0f);
	pos[0x0A] = VectorF3(1.0f, 1.0f, 0.0f + f___);
	pos[0x0B] = VectorF3(1.0f, 1.0f, 1.0f - f___);
	pos[0x0C] = VectorF3(1.0f - f___, 1.0f, 1.0f);
	pos[0x0D] = VectorF3(0.0f + f___, 1.0f, 1.0f);
	pos[0x0E] = VectorF3(0.0f, 1.0f, 1.0f - f___);
	pos[0x0F] = VectorF3(0.0f, 1.0f, 0.0f + f___);

	Quad0(GraphicsDataF.PrevZ, pos[0x0], pos[0x1], pos[0x8], pos[0x9], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 2);
	Quad0(GraphicsDataF.Here , pos[0x1], pos[0x2], pos[0x9], pos[0xA], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 2);

	Quad1(GraphicsDataF.NextX, pos[0x2], pos[0x3], pos[0xA], pos[0xB], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 3);
	Quad1(GraphicsDataF.Here , pos[0x3], pos[0x4], pos[0xB], pos[0xC], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 3);

	Quad0(GraphicsDataF.NextZ, pos[0x4], pos[0x5], pos[0xC], pos[0xD], BoxF2(VectorF2(1.0f, 0.0f), VectorF2(0.0f, 1.0f)), 5);
	Quad0(GraphicsDataF.Here , pos[0x5], pos[0x6], pos[0xD], pos[0xE], BoxF2(VectorF2(1.0f, 0.0f), VectorF2(0.0f, 1.0f)), 5);

	Quad1(GraphicsDataF.PrevX, pos[0x6], pos[0x7], pos[0xE], pos[0xF], BoxF2(VectorF2(0.0f, 1.0f), VectorF2(1.0f, 0.0f)), 0);
	Quad1(GraphicsDataF.Here , pos[0x7], pos[0x0], pos[0xF], pos[0x8], BoxF2(VectorF2(0.0f, 1.0f), VectorF2(1.0f, 0.0f)), 0);

	VoxelGraphicsDataF::Face	tri;
	VoxelGraphicsDataF::Vertex	pY[8];
	pY[0x0] = VoxelGraphicsDataF::Vertex(pos[0x0], VectorF3(0.0f, 0.0f + f___, 1));
	pY[0x1] = VoxelGraphicsDataF::Vertex(pos[0x1], VectorF3(0.0f, 1.0f - f___, 1));
	pY[0x2] = VoxelGraphicsDataF::Vertex(pos[0x2], VectorF3(0.0f + f___, 1.0f, 1));
	pY[0x3] = VoxelGraphicsDataF::Vertex(pos[0x3], VectorF3(1.0f - f___, 1.0f, 1));
	pY[0x4] = VoxelGraphicsDataF::Vertex(pos[0x4], VectorF3(1.0f, 1.0f - f___, 1));
	pY[0x5] = VoxelGraphicsDataF::Vertex(pos[0x5], VectorF3(1.0f, 0.0f + f___, 1));
	pY[0x6] = VoxelGraphicsDataF::Vertex(pos[0x6], VectorF3(1.0f - f___, 0.0f, 1));
	pY[0x7] = VoxelGraphicsDataF::Vertex(pos[0x7], VectorF3(0.0f + f___, 0.0f, 1));

	tri.Vertexes[0] = pY[0x0];
	tri.Vertexes[1] = pY[0x1];
	tri.Vertexes[2] = pY[0x5];
	GraphicsDataF.PrevY.Data.Insert(tri);
	tri.Vertexes[0] = pY[0x5];
	tri.Vertexes[1] = pY[0x1];
	tri.Vertexes[2] = pY[0x4];
	GraphicsDataF.PrevY.Data.Insert(tri);
	
	tri.Vertexes[0] = pY[0x1];
	tri.Vertexes[1] = pY[0x2];
	tri.Vertexes[2] = pY[0x4];
	GraphicsDataF.PrevY.Data.Insert(tri);
	tri.Vertexes[0] = pY[0x4];
	tri.Vertexes[1] = pY[0x2];
	tri.Vertexes[2] = pY[0x3];
	GraphicsDataF.PrevY.Data.Insert(tri);
	
	tri.Vertexes[0] = pY[0x5];
	tri.Vertexes[1] = pY[0x6];
	tri.Vertexes[2] = pY[0x0];
	GraphicsDataF.PrevY.Data.Insert(tri);
	tri.Vertexes[0] = pY[0x0];
	tri.Vertexes[1] = pY[0x6];
	tri.Vertexes[2] = pY[0x7];
	GraphicsDataF.PrevY.Data.Insert(tri);

	VoxelGraphicsDataF::Vertex	nY[16];
	nY[0x8] = VoxelGraphicsDataF::Vertex(pos[0x8], VectorF3(0.0f, 0.0f + f___, 4));
	nY[0x9] = VoxelGraphicsDataF::Vertex(pos[0x9], VectorF3(0.0f, 1.0f - f___, 4));
	nY[0xA] = VoxelGraphicsDataF::Vertex(pos[0xA], VectorF3(0.0f + f___, 1.0f, 4));
	nY[0xB] = VoxelGraphicsDataF::Vertex(pos[0xB], VectorF3(1.0f - f___, 1.0f, 4));
	nY[0xC] = VoxelGraphicsDataF::Vertex(pos[0xC], VectorF3(1.0f, 1.0f - f___, 4));
	nY[0xD] = VoxelGraphicsDataF::Vertex(pos[0xD], VectorF3(1.0f, 0.0f + f___, 4));
	nY[0xE] = VoxelGraphicsDataF::Vertex(pos[0xE], VectorF3(1.0f - f___, 0.0f, 4));
	nY[0xF] = VoxelGraphicsDataF::Vertex(pos[0xF], VectorF3(0.0f + f___, 0.0f, 4));

	tri.Vertexes[0] = nY[0xE];
	tri.Vertexes[1] = nY[0xD];
	tri.Vertexes[2] = nY[0xF];
	GraphicsDataF.NextY.Data.Insert(tri);

	tri.Vertexes[0] = nY[0xF];
	tri.Vertexes[1] = nY[0xD];
	tri.Vertexes[2] = nY[0x8];
	GraphicsDataF.NextY.Data.Insert(tri);

	tri.Vertexes[0] = nY[0x8];
	tri.Vertexes[1] = nY[0xD];
	tri.Vertexes[2] = nY[0xC];
	GraphicsDataF.NextY.Data.Insert(tri);

	tri.Vertexes[0] = nY[0x8];
	tri.Vertexes[1] = nY[0xC];
	tri.Vertexes[2] = nY[0x9];
	GraphicsDataF.NextY.Data.Insert(tri);

	tri.Vertexes[0] = nY[0x9];
	tri.Vertexes[1] = nY[0xC];
	tri.Vertexes[2] = nY[0xB];
	GraphicsDataF.NextY.Data.Insert(tri);

	tri.Vertexes[0] = nY[0x9];
	tri.Vertexes[1] = nY[0xB];
	tri.Vertexes[2] = nY[0xA];
	GraphicsDataF.NextY.Data.Insert(tri);

	GraphicsDataF.Done();
}

void VoxelGeometryPallet::InitSlope()
{
	unsigned int Texture = 0;

	HidePrevX = false;
	HidePrevY = true;
	HidePrevZ = false;

	HideNextX = false;
	HideNextY = false;
	HideNextZ = true;

	OrientationAxis0 = AxisRel::NextY;
	OrientationAxis1 = AxisRel::NextZ;

	VectorF3 pos[8];

	pos[0b000] = VectorF3(0.0f, 0.0f, 0.0f);
	pos[0b001] = VectorF3(1.0f, 0.0f, 0.0f);
	pos[0b010] = VectorF3(0.0f, 1.0f, 0.0f);
	pos[0b011] = VectorF3(1.0f, 1.0f, 0.0f);
	pos[0b100] = VectorF3(0.0f, 0.0f, 1.0f);
	pos[0b101] = VectorF3(1.0f, 0.0f, 1.0f);
	pos[0b110] = VectorF3(0.0f, 1.0f, 1.0f);
	pos[0b111] = VectorF3(1.0f, 1.0f, 1.0f);

	Quad0(GraphicsDataF.PrevY, pos[0b000], pos[0b100], pos[0b001], pos[0b101], BoxF2(VectorF2(0.25f, 0.0f), VectorF2(0.50f, 0.5f)), Texture);
	Quad1(GraphicsDataF.NextZ, pos[0b100], pos[0b110], pos[0b101], pos[0b111], BoxF2(VectorF2(0.50f, 0.5f), VectorF2(0.75f, 1.0f)), Texture);

	VoxelGraphicsDataF::Face	tri;

	tri.Vertexes[0] = VoxelGraphicsDataF::Vertex(pos[0b000], VectorF3(0.00f, 0.0f, Texture));
	tri.Vertexes[1] = VoxelGraphicsDataF::Vertex(pos[0b100], VectorF3(0.00f, 0.5f, Texture));
	tri.Vertexes[2] = VoxelGraphicsDataF::Vertex(pos[0b110], VectorF3(0.25f, 0.5f, Texture));
	GraphicsDataF.PrevX.Data.Insert(tri);

	tri.Vertexes[0] = VoxelGraphicsDataF::Vertex(pos[0b101], VectorF3(0.00f, 1.0f, Texture));
	tri.Vertexes[1] = VoxelGraphicsDataF::Vertex(pos[0b001], VectorF3(0.00f, 0.5f, Texture));
	tri.Vertexes[2] = VoxelGraphicsDataF::Vertex(pos[0b111], VectorF3(0.25f, 1.0f, Texture));
	GraphicsDataF.NextX.Data.Insert(tri);

	Quad0(GraphicsDataF.Here, pos[0b000], pos[0b001], pos[0b110], pos[0b111], BoxF2(VectorF2(0.75f, 0.0f), VectorF2(1.00f, 1.0f)), Texture);

	GraphicsDataF.Done();
}

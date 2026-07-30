#include "PalletGeometry.hpp"

#include "ValueType/Box/F2.hpp"
#include "ValueType/Box/U2.hpp"



VoxelPalletGeometry VoxelPalletGeometry::Cube;
VoxelPalletGeometry VoxelPalletGeometry::AxisStar;
VoxelPalletGeometry VoxelPalletGeometry::PrismY8;
VoxelPalletGeometry VoxelPalletGeometry::Slope;



const VoxelGeometryDataU::Face & VoxelPalletGeometry::AxisDataU(AxisRel axis) const
{
	switch (axis)
	{
		case AxisRel::PrevX: return DataU.PrevX;
		case AxisRel::PrevY: return DataU.PrevY;
		case AxisRel::PrevZ: return DataU.PrevZ;
		case AxisRel::NextX: return DataU.NextX;
		case AxisRel::NextY: return DataU.NextY;
		case AxisRel::NextZ: return DataU.NextZ;
		default: break;
	}
	throw "VoxelPalletGeometry::AxisDataU: Invalid axis\n";
}
const VoxelGeometryDataF::Axis & VoxelPalletGeometry::AxisDataF(AxisRel axis) const
{
	switch (axis)
	{
		case AxisRel::PrevX: return DataF.PrevX;
		case AxisRel::PrevY: return DataF.PrevY;
		case AxisRel::PrevZ: return DataF.PrevZ;
		case AxisRel::NextX: return DataF.NextX;
		case AxisRel::NextY: return DataF.NextY;
		case AxisRel::NextZ: return DataF.NextZ;
		default: return DataF.Here;
	}
	throw "VoxelPalletGeometry::AxisDataF: Invalid axis\n";
}



bool VoxelPalletGeometry::IsAxisVisible(AxisRel axis) const
{
	switch (axis)
	{
		case AxisRel::None:  return false;
		case AxisRel::PrevX: return UseF_PrevX;
		case AxisRel::PrevY: return UseF_PrevY;
		case AxisRel::PrevZ: return UseF_PrevZ;
		case AxisRel::NextX: return UseF_NextX;
		case AxisRel::NextY: return UseF_NextY;
		case AxisRel::NextZ: return UseF_NextZ;
		case AxisRel::Here:  return true;
		default: return false;
	}
}

AxisOrientation VoxelPalletGeometry::Orient(AxisRel placeAxis0, AxisRel placeAxis1) const
{
	AxisOrientation orient;
	orient.make(OrientationAxis0, placeAxis0, OrientationAxis1, placeAxis1);
	return orient;
}



static void Quad0(VoxelGeometryDataU::Face & face_data,
	VectorU3 p00, VectorU3 p01, VectorU3 p10, VectorU3 p11,
	BoxU2 box, unsigned int tex)
{
	face_data.Vertexes[0b00].Pos = p00;
	face_data.Vertexes[0b01].Pos = p10;
	face_data.Vertexes[0b10].Pos = p01;
	face_data.Vertexes[0b11].Pos = p11;

	face_data.Vertexes[0b00].Tex = VectorU2(box.Min.X, box.Min.Y);
	face_data.Vertexes[0b01].Tex = VectorU2(box.Min.X, box.Max.Y);
	face_data.Vertexes[0b10].Tex = VectorU2(box.Max.X, box.Min.Y);
	face_data.Vertexes[0b11].Tex = VectorU2(box.Max.X, box.Max.Y);

	face_data.Vertexes[0b00].Idx = tex;
	face_data.Vertexes[0b01].Idx = tex;
	face_data.Vertexes[0b10].Idx = tex;
	face_data.Vertexes[0b11].Idx = tex;
}
static void Quad1(VoxelGeometryDataU::Face & face_data,
	VectorU3 p00, VectorU3 p01, VectorU3 p10, VectorU3 p11,
	BoxU2 box, unsigned int tex)
{
	face_data.Vertexes[0b00].Pos = p00;
	face_data.Vertexes[0b01].Pos = p10;
	face_data.Vertexes[0b10].Pos = p01;
	face_data.Vertexes[0b11].Pos = p11;

	face_data.Vertexes[0b00].Tex = VectorU2(box.Min.X, box.Min.Y);
	face_data.Vertexes[0b01].Tex = VectorU2(box.Max.X, box.Min.Y);
	face_data.Vertexes[0b10].Tex = VectorU2(box.Min.X, box.Max.Y);
	face_data.Vertexes[0b11].Tex = VectorU2(box.Max.X, box.Max.Y);

	face_data.Vertexes[0b00].Idx = tex;
	face_data.Vertexes[0b01].Idx = tex;
	face_data.Vertexes[0b10].Idx = tex;
	face_data.Vertexes[0b11].Idx = tex;
}

void VoxelPalletGeometry::InitU()
{
	VectorU3 pos[8] = {
		VectorU3(0, 0, 0),
		VectorU3(1, 0, 0),
		VectorU3(0, 1, 0),
		VectorU3(1, 1, 0),
		VectorU3(0, 0, 1),
		VectorU3(1, 0, 1),
		VectorU3(0, 1, 1),
		VectorU3(1, 1, 1),
	};

	Quad0(DataU.PrevX, pos[0b000], pos[0b010], pos[0b100], pos[0b110], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 0);
	Quad0(DataU.PrevY, pos[0b000], pos[0b100], pos[0b001], pos[0b101], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 1);
	Quad0(DataU.PrevZ, pos[0b000], pos[0b001], pos[0b010], pos[0b011], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 2);

	Quad1(DataU.NextX, pos[0b001], pos[0b101], pos[0b011], pos[0b111], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 3);
	Quad1(DataU.NextY, pos[0b010], pos[0b011], pos[0b110], pos[0b111], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 4);
	Quad1(DataU.NextZ, pos[0b100], pos[0b110], pos[0b101], pos[0b111], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 5);
}



static void Quad0(VoxelGeometryDataF::Axis & face_data,
	VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11,
	BoxF2 box, unsigned int tex)
{
	VoxelGraphicsDataF::Face face;
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p00, VectorF3(box.Min.X, box.Min.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p10, VectorF3(box.Min.X, box.Max.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p01, VectorF3(box.Max.X, box.Min.Y, tex));
	face_data.Data.Insert(face);
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p01, VectorF3(box.Max.X, box.Min.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p10, VectorF3(box.Min.X, box.Max.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p11, VectorF3(box.Max.X, box.Max.Y, tex));
	face_data.Data.Insert(face);
}
static void Quad1(VoxelGeometryDataF::Axis & face_data,
	VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11,
	BoxF2 box, unsigned int tex)
{
	VoxelGraphicsDataF::Face face;
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p00, VectorF3(box.Min.X, box.Min.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p10, VectorF3(box.Max.X, box.Min.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p01, VectorF3(box.Min.X, box.Max.Y, tex));
	face_data.Data.Insert(face);
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p01, VectorF3(box.Min.X, box.Max.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p10, VectorF3(box.Max.X, box.Min.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p11, VectorF3(box.Max.X, box.Max.Y, tex));
	face_data.Data.Insert(face);
}

static void Tri0(VoxelGeometryDataF::Axis & face_data,
	VectorF3 p0, VectorF3 p1, VectorF3 p2,
	VectorF2 t0, VectorF2 t1, VectorF2 t2,
	unsigned int tex)
{
	VoxelGraphicsDataF::Face face;
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p0, VectorF3(t0.X, t0.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p1, VectorF3(t1.X, t1.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p2, VectorF3(t2.X, t2.Y, tex));
	face_data.Data.Insert(face);
}
static void Tri1(VoxelGeometryDataF::Axis & face_data,
	VectorF3 p0, VectorF3 p1, VectorF3 p2,
	VectorF2 t0, VectorF2 t1, VectorF2 t2,
	unsigned int tex)
{
	VoxelGraphicsDataF::Face face;
	face.Vertexes[0] = VoxelGraphicsDataF::Vertex(p0, VectorF3(t0.X, t0.Y, tex));
	face.Vertexes[1] = VoxelGraphicsDataF::Vertex(p2, VectorF3(t2.X, t2.Y, tex));
	face.Vertexes[2] = VoxelGraphicsDataF::Vertex(p1, VectorF3(t1.X, t1.Y, tex));
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

void VoxelPalletGeometry::InitF_Cube()
{
	UseF_PrevX = false;
	UseF_PrevY = false;
	UseF_PrevZ = false;

	UseF_NextX = false;
	UseF_NextY = false;
	UseF_NextZ = false;

	OrientationAxis0 = AxisRel::None;
	OrientationAxis1 = AxisRel::None;

	VectorF3 pos[8] = {
		VectorF3(0.0f, 0.0f, 0.0f), // 0b000
		VectorF3(1.0f, 0.0f, 0.0f), // 0b001
		VectorF3(0.0f, 1.0f, 0.0f), // 0b010
		VectorF3(1.0f, 1.0f, 0.0f), // 0b011
		VectorF3(0.0f, 0.0f, 1.0f), // 0b100
		VectorF3(1.0f, 0.0f, 1.0f), // 0b101
		VectorF3(0.0f, 1.0f, 1.0f), // 0b110
		VectorF3(1.0f, 1.0f, 1.0f), // 0b111
	};

	Quad0(DataF.PrevX, pos[0b000], pos[0b010], pos[0b100], pos[0b110], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 0);
	Quad0(DataF.PrevY, pos[0b000], pos[0b100], pos[0b001], pos[0b101], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 1);
	Quad0(DataF.PrevZ, pos[0b000], pos[0b001], pos[0b010], pos[0b011], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 2);

	Quad1(DataF.NextX, pos[0b001], pos[0b101], pos[0b011], pos[0b111], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 3);
	Quad1(DataF.NextY, pos[0b010], pos[0b011], pos[0b110], pos[0b111], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 4);
	Quad1(DataF.NextZ, pos[0b100], pos[0b110], pos[0b101], pos[0b111], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 5);

	DataF.Done();
}

void VoxelPalletGeometry::InitF_AxisStar()
{
	UseF_PrevX = true;
	UseF_PrevY = true;
	UseF_PrevZ = true;
	UseF_NextX = true;
	UseF_NextY = true;
	UseF_NextZ = true;

	VectorF3 prevX(0.0f, 0.5f, 0.5f);
	VectorF3 prevY(0.5f, 0.0f, 0.5f);
	VectorF3 prevZ(0.5f, 0.5f, 0.0f);
	VectorF3 nextX(1.0f, 0.5f, 0.5f);
	VectorF3 nextY(0.5f, 1.0f, 0.5f);
	VectorF3 nextZ(0.5f, 0.5f, 1.0f);

	float min = 0.4f;
	float max = 0.6f;

	VectorF3 pos[8] = {
		VectorF3(min, min, min), // 0b000
		VectorF3(max, min, min), // 0b001
		VectorF3(min, max, min), // 0b010
		VectorF3(max, max, min), // 0b011
		VectorF3(min, min, max), // 0b100
		VectorF3(max, min, max), // 0b101
		VectorF3(min, max, max), // 0b110
		VectorF3(max, max, max), // 0b111
	};

	Tri1(DataF.Here, prevX, pos[0b000], pos[0b010], VectorF2(0.5f, 0.5f), VectorF2(0, 0), VectorF2(1, 0), 0);
	Tri1(DataF.Here, prevX, pos[0b010], pos[0b110], VectorF2(0.5f, 0.5f), VectorF2(1, 0), VectorF2(1, 1), 0);
	Tri1(DataF.Here, prevX, pos[0b110], pos[0b100], VectorF2(0.5f, 0.5f), VectorF2(1, 1), VectorF2(0, 1), 0);
	Tri1(DataF.Here, prevX, pos[0b100], pos[0b000], VectorF2(0.5f, 0.5f), VectorF2(0, 1), VectorF2(0, 0), 0);

	Tri1(DataF.Here, prevY, pos[0b000], pos[0b100], VectorF2(0.5f, 0.5f), VectorF2(0, 0), VectorF2(1, 0), 1);
	Tri1(DataF.Here, prevY, pos[0b100], pos[0b101], VectorF2(0.5f, 0.5f), VectorF2(1, 0), VectorF2(1, 1), 1);
	Tri1(DataF.Here, prevY, pos[0b101], pos[0b001], VectorF2(0.5f, 0.5f), VectorF2(1, 1), VectorF2(0, 1), 1);
	Tri1(DataF.Here, prevY, pos[0b001], pos[0b000], VectorF2(0.5f, 0.5f), VectorF2(0, 1), VectorF2(0, 0), 1);

	Tri1(DataF.Here, prevZ, pos[0b000], pos[0b001], VectorF2(0.5f, 0.5f), VectorF2(0, 0), VectorF2(1, 0), 2);
	Tri1(DataF.Here, prevZ, pos[0b001], pos[0b011], VectorF2(0.5f, 0.5f), VectorF2(1, 0), VectorF2(1, 1), 2);
	Tri1(DataF.Here, prevZ, pos[0b011], pos[0b010], VectorF2(0.5f, 0.5f), VectorF2(1, 1), VectorF2(0, 1), 2);
	Tri1(DataF.Here, prevZ, pos[0b010], pos[0b000], VectorF2(0.5f, 0.5f), VectorF2(0, 1), VectorF2(0, 0), 2);

	Tri0(DataF.Here, nextX, pos[0b111], pos[0b101], VectorF2(0.5f, 0.5f), VectorF2(1, 1), VectorF2(0, 1), 3);
	Tri0(DataF.Here, nextX, pos[0b101], pos[0b001], VectorF2(0.5f, 0.5f), VectorF2(0, 1), VectorF2(0, 0), 3);
	Tri0(DataF.Here, nextX, pos[0b001], pos[0b011], VectorF2(0.5f, 0.5f), VectorF2(0, 0), VectorF2(1, 0), 3);
	Tri0(DataF.Here, nextX, pos[0b011], pos[0b111], VectorF2(0.5f, 0.5f), VectorF2(1, 0), VectorF2(1, 1), 3);

	Tri0(DataF.Here, nextY, pos[0b111], pos[0b011], VectorF2(0.5f, 0.5f), VectorF2(1, 1), VectorF2(0, 1), 4);
	Tri0(DataF.Here, nextY, pos[0b011], pos[0b010], VectorF2(0.5f, 0.5f), VectorF2(0, 1), VectorF2(0, 0), 4);
	Tri0(DataF.Here, nextY, pos[0b010], pos[0b110], VectorF2(0.5f, 0.5f), VectorF2(0, 0), VectorF2(1, 0), 4);
	Tri0(DataF.Here, nextY, pos[0b110], pos[0b111], VectorF2(0.5f, 0.5f), VectorF2(1, 0), VectorF2(1, 1), 4);

	Tri0(DataF.Here, nextZ, pos[0b111], pos[0b110], VectorF2(0.5f, 0.5f), VectorF2(1, 1), VectorF2(0, 1), 5);
	Tri0(DataF.Here, nextZ, pos[0b110], pos[0b100], VectorF2(0.5f, 0.5f), VectorF2(0, 1), VectorF2(0, 0), 5);
	Tri0(DataF.Here, nextZ, pos[0b100], pos[0b101], VectorF2(0.5f, 0.5f), VectorF2(0, 0), VectorF2(1, 0), 5);
	Tri0(DataF.Here, nextZ, pos[0b101], pos[0b111], VectorF2(0.5f, 0.5f), VectorF2(1, 0), VectorF2(1, 1), 5);
}
void VoxelPalletGeometry::InitF_PrismY8()
{
	UseF_PrevX = true;
	UseF_PrevY = true;
	UseF_PrevZ = true;
	UseF_NextX = true;
	UseF_NextY = true;
	UseF_NextZ = true;

	OrientationAxis0 = AxisRel::PrevY;
	OrientationAxis1 = AxisRel::None;

	float f___ = 0.3f;

	VectorF3 pos[16] = {
		VectorF3(0.0f + f___, 0.0f, 0.0f), // 0x0
		VectorF3(1.0f - f___, 0.0f, 0.0f), // 0x1
		VectorF3(1.0f, 0.0f, 0.0f + f___), // 0x2
		VectorF3(1.0f, 0.0f, 1.0f - f___), // 0x3
		VectorF3(1.0f - f___, 0.0f, 1.0f), // 0x4
		VectorF3(0.0f + f___, 0.0f, 1.0f), // 0x5
		VectorF3(0.0f, 0.0f, 1.0f - f___), // 0x6
		VectorF3(0.0f, 0.0f, 0.0f + f___), // 0x7
		VectorF3(0.0f + f___, 1.0f, 0.0f), // 0x8
		VectorF3(1.0f - f___, 1.0f, 0.0f), // 0x9
		VectorF3(1.0f, 1.0f, 0.0f + f___), // 0xA
		VectorF3(1.0f, 1.0f, 1.0f - f___), // 0xB
		VectorF3(1.0f - f___, 1.0f, 1.0f), // 0xC
		VectorF3(0.0f + f___, 1.0f, 1.0f), // 0xD
		VectorF3(0.0f, 1.0f, 1.0f - f___), // 0xE
		VectorF3(0.0f, 1.0f, 0.0f + f___), // 0xF
	};

	Quad0(DataF.PrevZ, pos[0x0], pos[0x1], pos[0x8], pos[0x9], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 2);
	Quad0(DataF.Here , pos[0x1], pos[0x2], pos[0x9], pos[0xA], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 2);

	Quad1(DataF.NextX, pos[0x2], pos[0x3], pos[0xA], pos[0xB], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 3);
	Quad1(DataF.Here , pos[0x3], pos[0x4], pos[0xB], pos[0xC], BoxF2(VectorF2(0.0f, 0.0f), VectorF2(1.0f, 1.0f)), 3);

	Quad0(DataF.NextZ, pos[0x4], pos[0x5], pos[0xC], pos[0xD], BoxF2(VectorF2(1.0f, 0.0f), VectorF2(0.0f, 1.0f)), 5);
	Quad0(DataF.Here , pos[0x5], pos[0x6], pos[0xD], pos[0xE], BoxF2(VectorF2(1.0f, 0.0f), VectorF2(0.0f, 1.0f)), 5);

	Quad1(DataF.PrevX, pos[0x6], pos[0x7], pos[0xE], pos[0xF], BoxF2(VectorF2(0.0f, 1.0f), VectorF2(1.0f, 0.0f)), 0);
	Quad1(DataF.Here , pos[0x7], pos[0x0], pos[0xF], pos[0x8], BoxF2(VectorF2(0.0f, 1.0f), VectorF2(1.0f, 0.0f)), 0);

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
	DataF.PrevY.Data.Insert(tri);
	tri.Vertexes[0] = pY[0x5];
	tri.Vertexes[1] = pY[0x1];
	tri.Vertexes[2] = pY[0x4];
	DataF.PrevY.Data.Insert(tri);
	
	tri.Vertexes[0] = pY[0x1];
	tri.Vertexes[1] = pY[0x2];
	tri.Vertexes[2] = pY[0x4];
	DataF.PrevY.Data.Insert(tri);
	tri.Vertexes[0] = pY[0x4];
	tri.Vertexes[1] = pY[0x2];
	tri.Vertexes[2] = pY[0x3];
	DataF.PrevY.Data.Insert(tri);
	
	tri.Vertexes[0] = pY[0x5];
	tri.Vertexes[1] = pY[0x6];
	tri.Vertexes[2] = pY[0x0];
	DataF.PrevY.Data.Insert(tri);
	tri.Vertexes[0] = pY[0x0];
	tri.Vertexes[1] = pY[0x6];
	tri.Vertexes[2] = pY[0x7];
	DataF.PrevY.Data.Insert(tri);

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
	DataF.NextY.Data.Insert(tri);

	tri.Vertexes[0] = nY[0xF];
	tri.Vertexes[1] = nY[0xD];
	tri.Vertexes[2] = nY[0x8];
	DataF.NextY.Data.Insert(tri);

	tri.Vertexes[0] = nY[0x8];
	tri.Vertexes[1] = nY[0xD];
	tri.Vertexes[2] = nY[0xC];
	DataF.NextY.Data.Insert(tri);

	tri.Vertexes[0] = nY[0x8];
	tri.Vertexes[1] = nY[0xC];
	tri.Vertexes[2] = nY[0x9];
	DataF.NextY.Data.Insert(tri);

	tri.Vertexes[0] = nY[0x9];
	tri.Vertexes[1] = nY[0xC];
	tri.Vertexes[2] = nY[0xB];
	DataF.NextY.Data.Insert(tri);

	tri.Vertexes[0] = nY[0x9];
	tri.Vertexes[1] = nY[0xB];
	tri.Vertexes[2] = nY[0xA];
	DataF.NextY.Data.Insert(tri);

	DataF.Done();
}

void VoxelPalletGeometry::InitF_Slope()
{
	UseF_PrevX = true;
	UseF_PrevY = false;
	UseF_PrevZ = true;

	UseF_NextX = true;
	UseF_NextY = true;
	UseF_NextZ = false;

	OrientationAxis0 = AxisRel::NextY;
	OrientationAxis1 = AxisRel::NextZ;

	VectorF3 pos[8] = {
		VectorF3(0.0f, 0.0f, 0.0f), // 0b000
		VectorF3(1.0f, 0.0f, 0.0f), // 0b001
		VectorF3(0.0f, 1.0f, 0.0f), // 0b010
		VectorF3(1.0f, 1.0f, 0.0f), // 0b011
		VectorF3(0.0f, 0.0f, 1.0f), // 0b100
		VectorF3(1.0f, 0.0f, 1.0f), // 0b101
		VectorF3(0.0f, 1.0f, 1.0f), // 0b110
		VectorF3(1.0f, 1.0f, 1.0f), // 0b111
	};

//	Quad0(DataF.PrevY, pos[0b000], pos[0b100], pos[0b001], pos[0b101], BoxF2(VectorF2(0.25f, 0.0f), VectorF2(0.50f, 0.5f)), Texture);
//	Quad1(DataF.NextZ, pos[0b100], pos[0b110], pos[0b101], pos[0b111], BoxF2(VectorF2(0.50f, 0.5f), VectorF2(0.75f, 1.0f)), Texture);

	Tri0(DataF.PrevX,
		pos[0b000],
		pos[0b100],
		pos[0b110],
		VectorF2(0.0f, 0.0f),
		VectorF2(0.0f, 1.0f),
		VectorF2(1.0f, 1.0f),
		0
	);
	Tri1(DataF.PrevX,
		pos[0b001],
		pos[0b101],
		pos[0b111],
		VectorF2(0.0f, 0.0f),
		VectorF2(0.0f, 1.0f),
		VectorF2(1.0f, 1.0f),
		3
	);

	Quad0(DataF.Here, pos[0b000], pos[0b001], pos[0b110], pos[0b111], BoxF2(VectorF2(0.75f, 0.0f), VectorF2(1.00f, 1.0f)), 0);

	DataF.Done();
}

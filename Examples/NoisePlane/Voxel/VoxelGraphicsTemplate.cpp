#include "VoxelGraphicsTemplate.hpp"

#include "ValueType/BoxF2.hpp"



VoxelGraphicsTemplate VoxelGraphicsTemplate::Cube;
VoxelGraphicsTemplate VoxelGraphicsTemplate::Cylinder;
VoxelGraphicsTemplate VoxelGraphicsTemplate::Slope;



const VoxelGraphicsData & VoxelGraphicsTemplate::AxisData(AxisRel axis) const
{
	switch (axis)
	{
		case AxisRel::PrevX: return PrevX;
		case AxisRel::PrevY: return PrevY;
		case AxisRel::PrevZ: return PrevZ;
		case AxisRel::NextX: return NextX;
		case AxisRel::NextY: return NextY;
		case AxisRel::NextZ: return NextZ;
		default: return Here;
	}
}

bool VoxelGraphicsTemplate::Visible(AxisRel axis) const
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

VoxelOrientation VoxelGraphicsTemplate::Orient(AxisRel placeAxis0, AxisRel placeAxis1) const
{
	VoxelOrientation orient;
	orient.make(OrientationAxis0, placeAxis0, OrientationAxis1, placeAxis1);
	return orient;
}



static void Quad0(VoxelGraphicsData & face, VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11, BoxF2 box, float tex)
{
	VoxelGraphics::MainTriangle	tri;
	tri.Corners[0] = VoxelGraphics::MainData(p00, VectorF3(box.Min.X, box.Min.Y, tex));
	tri.Corners[1] = VoxelGraphics::MainData(p10, VectorF3(box.Min.X, box.Max.Y, tex));
	tri.Corners[2] = VoxelGraphics::MainData(p01, VectorF3(box.Max.X, box.Min.Y, tex));
	face.Data.Insert(tri);
	tri.Corners[0] = VoxelGraphics::MainData(p01, VectorF3(box.Max.X, box.Min.Y, tex));
	tri.Corners[1] = VoxelGraphics::MainData(p10, VectorF3(box.Min.X, box.Max.Y, tex));
	tri.Corners[2] = VoxelGraphics::MainData(p11, VectorF3(box.Max.X, box.Max.Y, tex));
	face.Data.Insert(tri);
}
static void Quad1(VoxelGraphicsData & face, VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11, BoxF2 box, float tex)
{
	VoxelGraphics::MainTriangle	tri;
	tri.Corners[0] = VoxelGraphics::MainData(p00, VectorF3(box.Min.X, box.Min.Y, tex));
	tri.Corners[1] = VoxelGraphics::MainData(p10, VectorF3(box.Max.X, box.Min.Y, tex));
	tri.Corners[2] = VoxelGraphics::MainData(p01, VectorF3(box.Min.X, box.Max.Y, tex));
	face.Data.Insert(tri);
	tri.Corners[0] = VoxelGraphics::MainData(p01, VectorF3(box.Min.X, box.Max.Y, tex));
	tri.Corners[1] = VoxelGraphics::MainData(p10, VectorF3(box.Max.X, box.Min.Y, tex));
	tri.Corners[2] = VoxelGraphics::MainData(p11, VectorF3(box.Max.X, box.Max.Y, tex));
	face.Data.Insert(tri);
}



void VoxelGraphicsTemplate::InitCube()
{
	unsigned int Texture = 0;

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

	Quad0(PrevX, pos[0b000], pos[0b010], pos[0b100], pos[0b110], BoxF2(VectorF2(0.00f, 0.0f), VectorF2(0.25f, 0.5f)), Texture);
	Quad0(PrevY, pos[0b000], pos[0b100], pos[0b001], pos[0b101], BoxF2(VectorF2(0.25f, 0.0f), VectorF2(0.50f, 0.5f)), Texture);
	Quad0(PrevZ, pos[0b000], pos[0b001], pos[0b010], pos[0b011], BoxF2(VectorF2(0.50f, 0.0f), VectorF2(0.75f, 0.5f)), Texture);

	Quad1(NextX, pos[0b001], pos[0b101], pos[0b011], pos[0b111], BoxF2(VectorF2(0.00f, 0.5f), VectorF2(0.25f, 1.0f)), Texture);
	Quad1(NextY, pos[0b010], pos[0b011], pos[0b110], pos[0b111], BoxF2(VectorF2(0.25f, 0.5f), VectorF2(0.50f, 1.0f)), Texture);
	Quad1(NextZ, pos[0b100], pos[0b110], pos[0b101], pos[0b111], BoxF2(VectorF2(0.50f, 0.5f), VectorF2(0.75f, 1.0f)), Texture);
}

void VoxelGraphicsTemplate::InitCylinder()
{
	unsigned int Texture = 0;

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

	Quad0(PrevZ, pos[0x0], pos[0x1], pos[0x8], pos[0x9], BoxF2(VectorF2(0.50f, 0.0f), VectorF2(0.75f, 0.5f)), Texture);
	Quad0(Here , pos[0x1], pos[0x2], pos[0x9], pos[0xA], BoxF2(VectorF2(0.50f, 0.0f), VectorF2(0.75f, 0.5f)), Texture);
	Quad1(NextX, pos[0x2], pos[0x3], pos[0xA], pos[0xB], BoxF2(VectorF2(0.00f, 0.5f), VectorF2(0.25f, 1.0f)), Texture);
	Quad1(Here , pos[0x3], pos[0x4], pos[0xB], pos[0xC], BoxF2(VectorF2(0.00f, 0.5f), VectorF2(0.25f, 1.0f)), Texture);
	Quad0(NextZ, pos[0x4], pos[0x5], pos[0xC], pos[0xD], BoxF2(VectorF2(0.75f, 0.5f), VectorF2(0.50f, 1.0f)), Texture);
	Quad0(Here , pos[0x5], pos[0x6], pos[0xD], pos[0xE], BoxF2(VectorF2(0.75f, 0.5f), VectorF2(0.50f, 1.0f)), Texture);
	Quad1(PrevX, pos[0x6], pos[0x7], pos[0xE], pos[0xF], BoxF2(VectorF2(0.00f, 0.5f), VectorF2(0.25f, 0.0f)), Texture);
	Quad1(Here , pos[0x7], pos[0x0], pos[0xF], pos[0x8], BoxF2(VectorF2(0.00f, 0.5f), VectorF2(0.25f, 0.0f)), Texture);

	VoxelGraphics::MainTriangle	tri;
	VoxelGraphics::MainData pY[8];
	pY[0x0] = VoxelGraphics::MainData(pos[0x0], VectorF3(0.25f, 0.0f + 0.5f * f___, Texture));
	pY[0x1] = VoxelGraphics::MainData(pos[0x1], VectorF3(0.25f, 0.5f - 0.5f * f___, Texture));
	pY[0x2] = VoxelGraphics::MainData(pos[0x2], VectorF3(0.25f + 0.25f * f___, 0.5f, Texture));
	pY[0x3] = VoxelGraphics::MainData(pos[0x3], VectorF3(0.50f - 0.25f * f___, 0.5f, Texture));
	pY[0x4] = VoxelGraphics::MainData(pos[0x4], VectorF3(0.50f, 0.5f - 0.5f * f___, Texture));
	pY[0x5] = VoxelGraphics::MainData(pos[0x5], VectorF3(0.50f, 0.0f + 0.5f * f___, Texture));
	pY[0x6] = VoxelGraphics::MainData(pos[0x6], VectorF3(0.50f - 0.25f * f___, 0.0f, Texture));
	pY[0x7] = VoxelGraphics::MainData(pos[0x7], VectorF3(0.25f + 0.25f * f___, 0.0f, Texture));

	tri.Corners[0] = pY[0x0];
	tri.Corners[1] = pY[0x1];
	tri.Corners[2] = pY[0x5];
	PrevY.Data.Insert(tri);
	tri.Corners[0] = pY[0x5];
	tri.Corners[1] = pY[0x1];
	tri.Corners[2] = pY[0x4];
	PrevY.Data.Insert(tri);
	
	tri.Corners[0] = pY[0x1];
	tri.Corners[1] = pY[0x2];
	tri.Corners[2] = pY[0x4];
	PrevY.Data.Insert(tri);
	tri.Corners[0] = pY[0x4];
	tri.Corners[1] = pY[0x2];
	tri.Corners[2] = pY[0x3];
	PrevY.Data.Insert(tri);
	
	tri.Corners[0] = pY[0x5];
	tri.Corners[1] = pY[0x6];
	tri.Corners[2] = pY[0x0];
	PrevY.Data.Insert(tri);
	tri.Corners[0] = pY[0x0];
	tri.Corners[1] = pY[0x6];
	tri.Corners[2] = pY[0x7];
	PrevY.Data.Insert(tri);

	VoxelGraphics::MainData nY[16];
	nY[0x8] = VoxelGraphics::MainData(pos[0x8], VectorF3(0.25f, 0.5f + 0.5f * f___, Texture));
	nY[0x9] = VoxelGraphics::MainData(pos[0x9], VectorF3(0.25f, 1.0f - 0.5f * f___, Texture));
	nY[0xA] = VoxelGraphics::MainData(pos[0xA], VectorF3(0.25f + 0.25f * f___, 1.0f, Texture));
	nY[0xB] = VoxelGraphics::MainData(pos[0xB], VectorF3(0.50f - 0.25f * f___, 1.0f, Texture));
	nY[0xC] = VoxelGraphics::MainData(pos[0xC], VectorF3(0.50f, 1.0f - 0.5f * f___, Texture));
	nY[0xD] = VoxelGraphics::MainData(pos[0xD], VectorF3(0.50f, 0.5f + 0.5f * f___, Texture));
	nY[0xE] = VoxelGraphics::MainData(pos[0xE], VectorF3(0.50f - 0.25f * f___, 0.5f, Texture));
	nY[0xF] = VoxelGraphics::MainData(pos[0xF], VectorF3(0.25f + 0.25f * f___, 0.5f, Texture));

	tri.Corners[0] = nY[0xE];
	tri.Corners[1] = nY[0xD];
	tri.Corners[2] = nY[0xF];
	NextY.Data.Insert(tri);

	tri.Corners[0] = nY[0xF];
	tri.Corners[1] = nY[0xD];
	tri.Corners[2] = nY[0x8];
	NextY.Data.Insert(tri);

	tri.Corners[0] = nY[0x8];
	tri.Corners[1] = nY[0xD];
	tri.Corners[2] = nY[0xC];
	NextY.Data.Insert(tri);

	tri.Corners[0] = nY[0x8];
	tri.Corners[1] = nY[0xC];
	tri.Corners[2] = nY[0x9];
	NextY.Data.Insert(tri);

	tri.Corners[0] = nY[0x9];
	tri.Corners[1] = nY[0xC];
	tri.Corners[2] = nY[0xB];
	NextY.Data.Insert(tri);

	tri.Corners[0] = nY[0x9];
	tri.Corners[1] = nY[0xB];
	tri.Corners[2] = nY[0xA];
	NextY.Data.Insert(tri);
}

void VoxelGraphicsTemplate::InitSlope()
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

	Quad0(PrevY, pos[0b000], pos[0b100], pos[0b001], pos[0b101], BoxF2(VectorF2(0.25f, 0.0f), VectorF2(0.50f, 0.5f)), Texture);
	Quad1(NextZ, pos[0b100], pos[0b110], pos[0b101], pos[0b111], BoxF2(VectorF2(0.50f, 0.5f), VectorF2(0.75f, 1.0f)), Texture);

	VoxelGraphics::MainTriangle	tri;

	tri.Corners[0] = VoxelGraphics::MainData(pos[0b000], VectorF3(0.00f, 0.0f, Texture));
	tri.Corners[1] = VoxelGraphics::MainData(pos[0b100], VectorF3(0.00f, 0.5f, Texture));
	tri.Corners[2] = VoxelGraphics::MainData(pos[0b110], VectorF3(0.25f, 0.5f, Texture));
	PrevX.Data.Insert(tri);

	tri.Corners[0] = VoxelGraphics::MainData(pos[0b101], VectorF3(0.00f, 1.0f, Texture));
	tri.Corners[1] = VoxelGraphics::MainData(pos[0b001], VectorF3(0.00f, 0.5f, Texture));
	tri.Corners[2] = VoxelGraphics::MainData(pos[0b111], VectorF3(0.25f, 1.0f, Texture));
	NextX.Data.Insert(tri);

	Quad0(Here, pos[0b000], pos[0b001], pos[0b110], pos[0b111], BoxF2(VectorF2(0.75f, 0.0f), VectorF2(1.00f, 1.0f)), Texture);
}

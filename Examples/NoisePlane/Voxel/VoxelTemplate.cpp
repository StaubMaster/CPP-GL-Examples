#include "VoxelTemplate.hpp"
#include "VoxelOrientation.hpp"
#include "Voxel.hpp"

#include "ValueType/BoxF2.hpp"



VoxelTemplate VoxelTemplate::OrientationCube;
VoxelTemplate VoxelTemplate::OrientationCylinder;
VoxelTemplate VoxelTemplate::OrientationSlope;

VoxelTemplate VoxelTemplate::Gray;
VoxelTemplate VoxelTemplate::Grass;
VoxelTemplate VoxelTemplate::RedLog;



const Container::Binary<VoxelGraphics::MainData> & VoxelTemplate::AxisData(AxisRel axis) const
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
VoxelOrientation VoxelTemplate::Orient(AxisRel placeAxis0, AxisRel placeAxis1) const
{
	VoxelOrientation orient;
	orient.make(OrientationAxis0, placeAxis0, OrientationAxis1, placeAxis1);
	return orient;
}
Voxel VoxelTemplate::ToVoxel(AxisRel placeAxis0, AxisRel placeAxis1) const
{
	Voxel voxel;
	voxel.Template = this;
	voxel.Orientation = Orient(placeAxis0, placeAxis1);
	return voxel;
}



VoxelTemplate::~VoxelTemplate()
{ }
VoxelTemplate::VoxelTemplate()

{ }

//VoxelTemplate::VoxelTemplate(const VoxelTemplate & other);
//VoxelTemplate & VoxelTemplate::operator=(const VoxelTemplate & other);



static void Quad0(Container::Binary<VoxelGraphics::MainData> & data, VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11, BoxF2 box, float tex)
{
	data.Insert(VoxelGraphics::MainData(p00, VectorF3(box.Min.X, box.Min.Y, tex)));
	data.Insert(VoxelGraphics::MainData(p10, VectorF3(box.Min.X, box.Max.Y, tex)));
	data.Insert(VoxelGraphics::MainData(p01, VectorF3(box.Max.X, box.Min.Y, tex)));
	data.Insert(VoxelGraphics::MainData(p01, VectorF3(box.Max.X, box.Min.Y, tex)));
	data.Insert(VoxelGraphics::MainData(p10, VectorF3(box.Min.X, box.Max.Y, tex)));
	data.Insert(VoxelGraphics::MainData(p11, VectorF3(box.Max.X, box.Max.Y, tex)));
}
static void Quad1(Container::Binary<VoxelGraphics::MainData> & data, VectorF3 p00, VectorF3 p01, VectorF3 p10, VectorF3 p11, BoxF2 box, float tex)
{
	data.Insert(VoxelGraphics::MainData(p00, VectorF3(box.Min.X, box.Min.Y, tex)));
	data.Insert(VoxelGraphics::MainData(p10, VectorF3(box.Max.X, box.Min.Y, tex)));
	data.Insert(VoxelGraphics::MainData(p01, VectorF3(box.Min.X, box.Max.Y, tex)));
	data.Insert(VoxelGraphics::MainData(p01, VectorF3(box.Min.X, box.Max.Y, tex)));
	data.Insert(VoxelGraphics::MainData(p10, VectorF3(box.Max.X, box.Min.Y, tex)));
	data.Insert(VoxelGraphics::MainData(p11, VectorF3(box.Max.X, box.Max.Y, tex)));
}



void VoxelTemplate::InitCube(unsigned int tex)
{
	Texture = tex;

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

void VoxelTemplate::InitCylinder(unsigned int tex)
{
	Texture = tex;

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

	VoxelGraphics::MainData pY[8];
	pY[0x0] = VoxelGraphics::MainData(pos[0x0], VectorF3(0.25f, 0.0f + 0.5f * f___, tex));
	pY[0x1] = VoxelGraphics::MainData(pos[0x1], VectorF3(0.25f, 0.5f - 0.5f * f___, tex));
	pY[0x2] = VoxelGraphics::MainData(pos[0x2], VectorF3(0.25f + 0.25f * f___, 0.5f, tex));
	pY[0x3] = VoxelGraphics::MainData(pos[0x3], VectorF3(0.50f - 0.25f * f___, 0.5f, tex));
	pY[0x4] = VoxelGraphics::MainData(pos[0x4], VectorF3(0.50f, 0.5f - 0.5f * f___, tex));
	pY[0x5] = VoxelGraphics::MainData(pos[0x5], VectorF3(0.50f, 0.0f + 0.5f * f___, tex));
	pY[0x6] = VoxelGraphics::MainData(pos[0x6], VectorF3(0.50f - 0.25f * f___, 0.0f, tex));
	pY[0x7] = VoxelGraphics::MainData(pos[0x7], VectorF3(0.25f + 0.25f * f___, 0.0f, tex));

	PrevY.Insert(pY[0x0]);
	PrevY.Insert(pY[0x1]);
	PrevY.Insert(pY[0x5]);
	PrevY.Insert(pY[0x5]);
	PrevY.Insert(pY[0x1]);
	PrevY.Insert(pY[0x4]);

	PrevY.Insert(pY[0x1]);
	PrevY.Insert(pY[0x2]);
	PrevY.Insert(pY[0x4]);
	PrevY.Insert(pY[0x4]);
	PrevY.Insert(pY[0x2]);
	PrevY.Insert(pY[0x3]);

	PrevY.Insert(pY[0x5]);
	PrevY.Insert(pY[0x6]);
	PrevY.Insert(pY[0x0]);
	PrevY.Insert(pY[0x0]);
	PrevY.Insert(pY[0x6]);
	PrevY.Insert(pY[0x7]);

	VoxelGraphics::MainData nY[16];
	nY[0x8] = VoxelGraphics::MainData(pos[0x8], VectorF3(0.25f, 0.5f + 0.5f * f___, tex));
	nY[0x9] = VoxelGraphics::MainData(pos[0x9], VectorF3(0.25f, 1.0f - 0.5f * f___, tex));
	nY[0xA] = VoxelGraphics::MainData(pos[0xA], VectorF3(0.25f + 0.25f * f___, 1.0f, tex));
	nY[0xB] = VoxelGraphics::MainData(pos[0xB], VectorF3(0.50f - 0.25f * f___, 1.0f, tex));
	nY[0xC] = VoxelGraphics::MainData(pos[0xC], VectorF3(0.50f, 1.0f - 0.5f * f___, tex));
	nY[0xD] = VoxelGraphics::MainData(pos[0xD], VectorF3(0.50f, 0.5f + 0.5f * f___, tex));
	nY[0xE] = VoxelGraphics::MainData(pos[0xE], VectorF3(0.50f - 0.25f * f___, 0.5f, tex));
	nY[0xF] = VoxelGraphics::MainData(pos[0xF], VectorF3(0.25f + 0.25f * f___, 0.5f, tex));

	NextY.Insert(nY[0xE]);
	NextY.Insert(nY[0xD]);
	NextY.Insert(nY[0xF]);

	NextY.Insert(nY[0xF]);
	NextY.Insert(nY[0xD]);
	NextY.Insert(nY[0x8]);

	NextY.Insert(nY[0x8]);
	NextY.Insert(nY[0xD]);
	NextY.Insert(nY[0xC]);

	NextY.Insert(nY[0x8]);
	NextY.Insert(nY[0xC]);
	NextY.Insert(nY[0x9]);

	NextY.Insert(nY[0x9]);
	NextY.Insert(nY[0xC]);
	NextY.Insert(nY[0xB]);

	NextY.Insert(nY[0x9]);
	NextY.Insert(nY[0xB]);
	NextY.Insert(nY[0xA]);
}

void VoxelTemplate::InitSlope(unsigned int tex)
{
	Texture = tex;

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

	PrevX.Insert(VoxelGraphics::MainData(pos[0b000], VectorF3(0.00f, 0.0f, tex)));
	PrevX.Insert(VoxelGraphics::MainData(pos[0b100], VectorF3(0.00f, 0.5f, tex)));
	PrevX.Insert(VoxelGraphics::MainData(pos[0b110], VectorF3(0.25f, 0.5f, tex)));

	NextX.Insert(VoxelGraphics::MainData(pos[0b101], VectorF3(0.00f, 1.0f, tex)));
	NextX.Insert(VoxelGraphics::MainData(pos[0b001], VectorF3(0.00f, 0.5f, tex)));
	NextX.Insert(VoxelGraphics::MainData(pos[0b111], VectorF3(0.25f, 1.0f, tex)));

	Quad0(Here, pos[0b000], pos[0b001], pos[0b110], pos[0b111], BoxF2(VectorF2(0.75f, 0.0f), VectorF2(1.00f, 1.0f)), Texture);
}
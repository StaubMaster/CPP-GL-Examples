#include "VoxelOrientation.hpp"



::Diag VoxelOrientation::GetDiag() const { return (Diag)((Value & 0b00000111) >> 0); }
::Flip VoxelOrientation::GetFlip() const { return (Flip)((Value & 0b00011000) >> 3); }

void VoxelOrientation::SetDiag(::Diag diag) { Value = (Value & (~0b00000111)) | (((unsigned char)diag) << 0); }
void VoxelOrientation::SetFlip(::Flip flip) { Value = (Value & (~0b00011000)) | (((unsigned char)flip) << 3); }



//void VoxelOrientation::make(::Diag diag, ::Flip flip) { Diag = diag; Flip = flip; }
void VoxelOrientation::make(::Diag diag, ::Flip flip) { SetDiag(diag); SetFlip(flip); }



VoxelOrientation::~VoxelOrientation() { }
VoxelOrientation::VoxelOrientation()
//	: Diag(Diag::Here)
//	, Flip(Flip::None)
	: Value(0)
{ }

VoxelOrientation::VoxelOrientation(const VoxelOrientation & other)
//	: Diag(other.Diag)
//	, Flip(other.Flip)
	: Value(other.Value)
{ }
VoxelOrientation & VoxelOrientation::operator=(const VoxelOrientation & other)
{
//	Diag = other.Diag;
//	Flip = other.Flip;
	Value = other.Value;
	return *this;
}



/*void VoxelOrientation::make(Axis origin0, Axis target0, Axis origin1, Axis target1)
{
	(void)origin1;
	(void)target1;
	if (origin0 == Axis::PrevX)
	{
		if (target0 == Axis::PrevX)
		{
			if (origin1 == Axis::Here)
			{
				if (target1 == Axis::Here) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::Regular); }
			}
			if (origin1 == Axis::PrevY)
			{
				if (target1 == Axis::PrevY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::Regular); }
				//if (target1 == Axis::PrevZ) { make(Vector3MixerSigns::KeepZ, Vector3MixerOrder::Prev, Vector3MixerReverse::ReverseZ); }
				if (target1 == Axis::PrevZ) { make(Vector3MixerSigns::KeepZ, Vector3MixerOrder::Here, Vector3MixerReverse::ReverseX); }
				//if (target1 == Axis::PrevZ) { make(Vector3MixerSigns::KeepZ, Vector3MixerOrder::Next, Vector3MixerReverse::ReverseY); }
				if (target1 == Axis::NextY) { make(Vector3MixerSigns::KeepX , Vector3MixerOrder::Here, Vector3MixerReverse::Regular); }
				if (target1 == Axis::NextZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::Regular); }
			}
		}
		if (target0 == Axis::PrevY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Prev, Vector3MixerReverse::Regular); }
		if (target0 == Axis::PrevZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Next, Vector3MixerReverse::Regular); }
		if (target0 == Axis::NextX) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::ReverseX); }
		if (target0 == Axis::NextY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Next, Vector3MixerReverse::ReverseX); }
		if (target0 == Axis::NextZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Prev, Vector3MixerReverse::ReverseX); }
	}
	if (origin0 == Axis::PrevY)
	{
		if (target0 == Axis::PrevX) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Next, Vector3MixerReverse::Regular); }
		if (target0 == Axis::PrevY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::Regular); }
		if (target0 == Axis::PrevZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Prev, Vector3MixerReverse::Regular); }
		if (target0 == Axis::NextX) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Prev, Vector3MixerReverse::ReverseY); }
		if (target0 == Axis::NextY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::ReverseY); }
		if (target0 == Axis::NextZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Next, Vector3MixerReverse::ReverseY); }
	}
	if (origin0 == Axis::PrevZ)
	{
		if (target0 == Axis::PrevX) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Prev, Vector3MixerReverse::Regular); }
		if (target0 == Axis::PrevY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Next, Vector3MixerReverse::Regular); }
		if (target0 == Axis::PrevZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::Regular); }
		if (target0 == Axis::NextX) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Next, Vector3MixerReverse::ReverseZ); }
		if (target0 == Axis::NextY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Prev, Vector3MixerReverse::ReverseZ); }
		if (target0 == Axis::NextZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::ReverseZ); }
	}
	if (origin0 == Axis::NextX)
	{
		if (target0 == Axis::PrevX) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::ReverseX); }
		if (target0 == Axis::PrevY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Next, Vector3MixerReverse::ReverseX); }
		if (target0 == Axis::PrevZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Prev, Vector3MixerReverse::ReverseX); }
		if (target0 == Axis::NextX) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::Regular); }
		if (target0 == Axis::NextY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Prev, Vector3MixerReverse::Regular); }
		if (target0 == Axis::NextZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Next, Vector3MixerReverse::Regular); }
	}
	if (origin0 == Axis::NextY)
	{
		if (target0 == Axis::PrevX) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Prev, Vector3MixerReverse::ReverseY); }
		if (target0 == Axis::PrevY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::ReverseY); }
		if (target0 == Axis::PrevZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Next, Vector3MixerReverse::ReverseY); }
		if (target0 == Axis::NextX) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Next, Vector3MixerReverse::Regular); }
		if (target0 == Axis::NextY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::Regular); }
		if (target0 == Axis::NextZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Prev, Vector3MixerReverse::Regular); }
	}
	if (origin0 == Axis::NextZ)
	{
		if (target0 == Axis::PrevX) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Next, Vector3MixerReverse::ReverseZ); }
		if (target0 == Axis::PrevY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Prev, Vector3MixerReverse::ReverseZ); }
		if (target0 == Axis::PrevZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::ReverseZ); }
		if (target0 == Axis::NextX) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Prev, Vector3MixerReverse::Regular); }
		if (target0 == Axis::NextY) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Next, Vector3MixerReverse::Regular); }
		if (target0 == Axis::NextZ) { make(Vector3MixerSigns::Normal, Vector3MixerOrder::Here, Vector3MixerReverse::Regular); }
	}
}*/


/*
	origin0 and target0 can be 6 Axis
	origin1 and target1 can be 4 Axis
	6 * 6 * 4 * 4 = 576
	dont feel like hardcoding all that
	how to automate ?
	origin1 and target1 only spins
	which is 1 of 4 combinations
	figure out the spin offset and use that ?
*/



/*
static unsigned char AxisXSpin(Axis axis)
{
	if (axis == Axis::PrevY) { return 0; }
	if (axis == Axis::PrevZ) { return 1; }
	if (axis == Axis::NextY) { return 2; }
	if (axis == Axis::NextZ) { return 3; }
	return 0xFF;
}
static unsigned char AxisYSpin(Axis axis)
{
	if (axis == Axis::PrevX) { return 0; }
	if (axis == Axis::PrevZ) { return 1; }
	if (axis == Axis::NextX) { return 2; }
	if (axis == Axis::NextZ) { return 3; }
	return 0xFF;
}
static unsigned char AxisSpin(unsigned char origin, unsigned char target)
{
	if (origin == 0xFF) { return 0xFF; }
	if (target == 0xFF) { return 0xFF; }
	if (target < origin)
	{
		target += 4;
	}
	return target - origin;
}
*/


/*
6 * 6 * 4 = 144
still dont feel like figuring that out
probably a pattern
*/



void VoxelOrientation::make(Axis origin0, Axis target0, Axis origin1, Axis target1)
{
//	Origin0 = origin0;
//	Target0 = target0;
//	Origin1 = origin1;
//	Target1 = target1;
	(void)origin1;
	(void)target1;

	if (origin0 == Axis::PrevX)
	{
		if (target0 == Axis::PrevX) { make(Diag::Here , Flip::None ); }
		if (target0 == Axis::PrevY) { make(Diag::Prev , Flip::None ); }
		if (target0 == Axis::PrevZ) { make(Diag::Next , Flip::None ); }
		if (target0 == Axis::NextX) { make(Diag::DiagX, Flip::None ); }
		if (target0 == Axis::NextY) { make(Diag::DiagZ, Flip::None ); }
		if (target0 == Axis::NextZ) { make(Diag::DiagY, Flip::None ); }
	}
	if (origin0 == Axis::PrevY)
	{
		if (target0 == Axis::PrevX) { make(Diag::Next , Flip::None ); }
		if (target0 == Axis::PrevY) { make(Diag::Here , Flip::None ); }
		if (target0 == Axis::PrevZ) { make(Diag::Prev , Flip::None ); }
		if (target0 == Axis::NextX) { make(Diag::DiagZ, Flip::None ); }
		if (target0 == Axis::NextY) { make(Diag::DiagY, Flip::None ); }
		if (target0 == Axis::NextZ) { make(Diag::DiagX, Flip::None ); }
	}
	if (origin0 == Axis::PrevZ)
	{
		if (target0 == Axis::PrevX) { make(Diag::Prev , Flip::None ); }
		if (target0 == Axis::PrevY) { make(Diag::Next , Flip::None ); }
		if (target0 == Axis::PrevZ) { make(Diag::Here , Flip::None ); }
		if (target0 == Axis::NextX) { make(Diag::DiagY, Flip::None ); }
		if (target0 == Axis::NextY) { make(Diag::DiagX, Flip::None ); }
		if (target0 == Axis::NextZ) { make(Diag::DiagZ, Flip::None ); }
	}

	if (origin0 == Axis::NextX)
	{
		if (target0 == Axis::PrevX) { make(Diag::DiagX, Flip::None ); }
		if (target0 == Axis::PrevY) { make(Diag::DiagZ, Flip::None ); }
		if (target0 == Axis::PrevZ) { make(Diag::DiagY, Flip::None ); }
		if (target0 == Axis::NextX) { make(Diag::Here , Flip::None ); }
		if (target0 == Axis::NextY) { make(Diag::Prev , Flip::None ); }
		if (target0 == Axis::NextZ) { make(Diag::Next , Flip::None ); }
	}
	if (origin0 == Axis::NextY)
	{
		if (target0 == Axis::PrevX) { make(Diag::DiagZ, Flip::None ); }
		if (target0 == Axis::PrevY) { make(Diag::DiagY, Flip::None ); }
		if (target0 == Axis::PrevZ) { make(Diag::DiagX, Flip::None ); }
		if (target0 == Axis::NextX) { make(Diag::Next , Flip::None ); }
		if (target0 == Axis::NextY) { make(Diag::Here , Flip::None ); }
		if (target0 == Axis::NextZ) { make(Diag::Prev , Flip::None ); }
	}
	if (origin0 == Axis::NextZ)
	{
		if (target0 == Axis::PrevX) { make(Diag::DiagY, Flip::None ); }
		if (target0 == Axis::PrevY) { make(Diag::DiagX, Flip::None ); }
		if (target0 == Axis::PrevZ) { make(Diag::DiagZ, Flip::None ); }
		if (target0 == Axis::NextX) { make(Diag::Prev , Flip::None ); }
		if (target0 == Axis::NextY) { make(Diag::Next , Flip::None ); }
		if (target0 == Axis::NextZ) { make(Diag::Here , Flip::None ); }
	}

	/*if (origin0 == Axis::PrevX)
	{
		if (target0 == Axis::PrevX)
		{
			unsigned char spin = AxisSpin(AxisXSpin(origin1), AxisXSpin(target1));
			if (spin == 0) { make(Diag::Here , Flip::None ); }
			if (spin == 1) { make(Diag::DiagX, Flip::FlipY); }
			if (spin == 2) { make(Diag::Here , Flip::FlipX); }
			if (spin == 3) { make(Diag::DiagX, Flip::FlipZ); }
		}
		if (target0 == Axis::PrevZ)
		{
			unsigned char spin = AxisSpin(AxisXSpin(origin1), AxisYSpin(target1));
			if (spin == 0) { make(Diag::Next , Flip::None ); }
			if (spin == 1) { make(Diag::DiagY, Flip::FlipX); }
			if (spin == 2) { make(Diag::Next , Flip::FlipZ); }
			if (spin == 3) { make(Diag::DiagY, Flip::FlipY); }
		}
	}*/
}

/*
SpinDiag rotates Axis
SpinDiagPrev(XYZ) = ZXY

FlipDiag swaps 2 Axis
FlipDiagX(XYZ) = XZY

FlipAxis "Invertes" 2 Axis
FlipAxisX(+++) = +--
*/

VectorF3 VoxelOrientation::orient(VectorF3 v) const
{
	//switch (Diag)
	switch (GetDiag())
	{
		case Diag::Here : v = VectorF3(v.X, v.Y, v.Z); break;
		case Diag::Prev : v = VectorF3(v.Z, v.X, v.Y); break;
		case Diag::Next : v = VectorF3(v.Y, v.Z, v.X); break;
		case Diag::DiagX: v = VectorF3(1 - v.X, 1 - v.Z, 1 - v.Y); break;
		case Diag::DiagY: v = VectorF3(1 - v.Z, 1 - v.Y, 1 - v.X); break;
		case Diag::DiagZ: v = VectorF3(1 - v.Y, 1 - v.X, 1 - v.Z); break;
	}

	//switch (Flip)
	switch (GetFlip())
	{
		case Flip::None : v = VectorF3(0 + v.X, 0 + v.Y, 0 + v.Z); break;
		case Flip::FlipX: v = VectorF3(0 + v.X, 1 - v.Y, 1 - v.Z); break;
		case Flip::FlipY: v = VectorF3(1 - v.X, 0 + v.Y, 1 - v.Z); break;
		case Flip::FlipZ: v = VectorF3(1 - v.X, 1 - v.Y, 0 + v.Z); break;
	}

	return v;
}

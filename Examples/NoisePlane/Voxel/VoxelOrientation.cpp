#include "VoxelOrientation.hpp"



/*
AxisPair::~AxisPair() { }
AxisPair::AxisPair()
	: Prev(::Axis::None)
	, Next(::Axis::None)
{ }
AxisPair::AxisPair(::Axis prev, ::Axis next)
	: Prev(prev)
	, Next(next)
{ }
AxisPair::AxisPair(const AxisPair & other)
	: Prev(other.Prev)
	, Next(other.Next)
{ }
AxisPair & AxisPair::operator=(const AxisPair & other)
{
	Prev = other.Prev;
	Next = other.Next;
	return *this;
}
AxisPair AxisPair::operator+() const { return AxisPair(Prev, Next); }
AxisPair AxisPair::operator-() const { return AxisPair(Next, Prev); }
AxisPair AxisPair::X() { return AxisPair(::Axis::PrevX, ::Axis::NextX); }
AxisPair AxisPair::Y() { return AxisPair(::Axis::PrevY, ::Axis::NextY); }
AxisPair AxisPair::Z() { return AxisPair(::Axis::PrevZ, ::Axis::NextZ); }
*/



/*
AxisOrientation::~AxisOrientation() { }
AxisOrientation::AxisOrientation()
	: X(AxisPair::X())
	, Y(AxisPair::Y())
	, Z(AxisPair::Z())
{ }
AxisOrientation::AxisOrientation(AxisPair x, AxisPair y, AxisPair z)
	: X(x)
	, Y(y)
	, Z(z)
{ }
AxisOrientation::AxisOrientation(const AxisOrientation & other)
	: X(other.X)
	, Y(other.Y)
	, Z(other.Z)
{ }
AxisOrientation & AxisOrientation::operator=(const AxisOrientation & other)
{
	X = other.X;
	Y = other.Y;
	Z = other.Z;
	return *this;
}
void AxisOrientation::make(::Diag diag, ::Flip flip)
{
	switch (diag)
	{
		case Diag::Here : *this = AxisOrientation(+X, +Y, +Z); break;
		case Diag::Prev : *this = AxisOrientation(+Z, +X, +Y); break;
		case Diag::Next : *this = AxisOrientation(+Y, +Z, +X); break;
		case Diag::DiagX: *this = AxisOrientation(-X, -Z, -Y); break;
		case Diag::DiagY: *this = AxisOrientation(-Z, -Y, -X); break;
		case Diag::DiagZ: *this = AxisOrientation(-Y, -X, -Z); break;
	}

	switch (flip)
	{
		case Flip::None : *this = AxisOrientation(+X, +Y, +Z); break;
		case Flip::FlipX: *this = AxisOrientation(+X, -Y, -Z); break;
		case Flip::FlipY: *this = AxisOrientation(-X, +Y, -Z); break;
		case Flip::FlipZ: *this = AxisOrientation(-X, -Y, +Z); break;
	}
}
*/



/*
Diag::Here : (+X, +Y, +Z)
Diag::Prev : (+Z, +X, +Y)
Diag::Next : (+Y, +Z, +X)
Diag::DiagX: (-X, -Z, -Y)
Diag::DiagY: (-Z, -Y, -X)
Diag::DiagZ: (-Y, -X, -Z)
*/
static ::Axis OrientAxis(::Axis axis, ::Diag diag)
{
	if (axis == ::Axis::PrevX)
	{
		switch (diag)
		{
			case Diag::Here : return ::Axis::PrevX; break;
			case Diag::Prev : return ::Axis::PrevY; break;
			case Diag::Next : return ::Axis::PrevZ; break;
			case Diag::DiagX: return ::Axis::NextX; break;
			case Diag::DiagY: return ::Axis::NextZ; break;
			case Diag::DiagZ: return ::Axis::NextY; break;
		}
	}
	if (axis == ::Axis::PrevY)
	{
		switch (diag)
		{
			case Diag::Here : return ::Axis::PrevY; break;
			case Diag::Prev : return ::Axis::PrevZ; break;
			case Diag::Next : return ::Axis::PrevX; break;
			case Diag::DiagX: return ::Axis::NextZ; break;
			case Diag::DiagY: return ::Axis::NextY; break;
			case Diag::DiagZ: return ::Axis::NextX; break;
		}
	}
	if (axis == ::Axis::PrevZ)
	{
		switch (diag)
		{
			case Diag::Here : return ::Axis::PrevZ; break;
			case Diag::Prev : return ::Axis::PrevX; break;
			case Diag::Next : return ::Axis::PrevY; break;
			case Diag::DiagX: return ::Axis::NextY; break;
			case Diag::DiagY: return ::Axis::NextX; break;
			case Diag::DiagZ: return ::Axis::NextZ; break;
		}
	}
	if (axis == ::Axis::NextX)
	{
		switch (diag)
		{
			case Diag::Here : return ::Axis::NextX; break;
			case Diag::Prev : return ::Axis::NextY; break;
			case Diag::Next : return ::Axis::NextZ; break;
			case Diag::DiagX: return ::Axis::PrevX; break;
			case Diag::DiagY: return ::Axis::PrevZ; break;
			case Diag::DiagZ: return ::Axis::PrevY; break;
		}
	}
	if (axis == ::Axis::NextY)
	{
		switch (diag)
		{
			case Diag::Here : return ::Axis::NextY; break;
			case Diag::Prev : return ::Axis::NextZ; break;
			case Diag::Next : return ::Axis::NextX; break;
			case Diag::DiagX: return ::Axis::PrevZ; break;
			case Diag::DiagY: return ::Axis::PrevY; break;
			case Diag::DiagZ: return ::Axis::PrevX; break;
		}
	}
	if (axis == ::Axis::NextZ)
	{
		switch (diag)
		{
			case Diag::Here : return ::Axis::NextZ; break;
			case Diag::Prev : return ::Axis::NextX; break;
			case Diag::Next : return ::Axis::NextY; break;
			case Diag::DiagX: return ::Axis::PrevY; break;
			case Diag::DiagY: return ::Axis::PrevX; break;
			case Diag::DiagZ: return ::Axis::PrevZ; break;
		}
	}
	return axis;
}

/*
Flip::None : (+X, +Y, +Z)
Flip::FlipX: (+X, -Y, -Z)
Flip::FlipY: (-X, +Y, -Z)
Flip::FlipZ: (-X, -Y, +Z)
*/
static ::Axis OrientAxis(::Axis axis, ::Flip flip)
{
	if (flip == Flip::None)
	{
		switch (axis)
		{
			case Axis::PrevX: return ::Axis::PrevX;
			case Axis::PrevY: return ::Axis::PrevY;
			case Axis::PrevZ: return ::Axis::PrevZ;
			case Axis::NextX: return ::Axis::NextX;
			case Axis::NextY: return ::Axis::NextY;
			case Axis::NextZ: return ::Axis::NextZ;
			default: return axis;
		}
	}
	if (flip == Flip::FlipX)
	{
		switch (axis)
		{
			case Axis::PrevX: return ::Axis::PrevX;
			case Axis::PrevY: return ::Axis::NextY;
			case Axis::PrevZ: return ::Axis::NextZ;
			case Axis::NextX: return ::Axis::NextX;
			case Axis::NextY: return ::Axis::PrevY;
			case Axis::NextZ: return ::Axis::PrevZ;
			default: return axis;
		}
	}
	if (flip == Flip::FlipY)
	{
		switch (axis)
		{
			case Axis::PrevX: return ::Axis::NextX;
			case Axis::PrevY: return ::Axis::PrevY;
			case Axis::PrevZ: return ::Axis::NextZ;
			case Axis::NextX: return ::Axis::PrevX;
			case Axis::NextY: return ::Axis::NextY;
			case Axis::NextZ: return ::Axis::PrevZ;
			default: return axis;
		}
	}
	if (flip == Flip::FlipZ)
	{
		switch (axis)
		{
			case Axis::PrevX: return ::Axis::NextX;
			case Axis::PrevY: return ::Axis::NextY;
			case Axis::PrevZ: return ::Axis::PrevZ;
			case Axis::NextX: return ::Axis::PrevX;
			case Axis::NextY: return ::Axis::PrevY;
			case Axis::NextZ: return ::Axis::NextZ;
			default: return axis;
		}
	}
	return axis;
}



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



VectorF3 VoxelOrientation::absolute(VectorF3 v) const
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
::Axis VoxelOrientation::absolute(Axis axis) const
{
	axis = ::OrientAxis(axis, GetDiag());
	axis = ::OrientAxis(axis, GetFlip());
	return axis;
}

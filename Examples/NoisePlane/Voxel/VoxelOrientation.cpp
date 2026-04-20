#include "VoxelOrientation.hpp"



/*AxisPair::~AxisPair() { }
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



/*AxisOrientation::~AxisOrientation() { }
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





Diag VoxelOrientation::GetDiag() const { return (Diag)((Value & 0b00000111) >> 0); }
Flip VoxelOrientation::GetFlip() const { return (Flip)((Value & 0b00011000) >> 3); }

void VoxelOrientation::SetDiag(Diag diag) { Value = (Value & (~0b00000111)) | (((unsigned char)diag) << 0); }
void VoxelOrientation::SetFlip(Flip flip) { Value = (Value & (~0b00011000)) | (((unsigned char)flip) << 3); }





//void VoxelOrientation::make(::Diag diag, ::Flip flip) { Diag = diag; Flip = flip; }
void VoxelOrientation::make(Diag diag, Flip flip) { SetDiag(diag); SetFlip(flip); }



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



// try out every combination
// make origin absolute or target relative
// then check if it matches the other
// check both
void VoxelOrientation::make(Axis origin0, Axis target0, Axis origin1, Axis target1)
{
	Diag diags[6] =
	{
		Diag::Here,
		Diag::Prev,
		Diag::Next,
		Diag::DiagX,
		Diag::DiagY,
		Diag::DiagZ,
	};
	Flip flips[4] = 
	{
		Flip::None,
		Flip::FlipX,
		Flip::FlipY,
		Flip::FlipZ,
	};
	VoxelOrientation orient;

	bool ignore0 = (origin0 == Axis::None || target0 == Axis::None);
	bool ignore1 = (origin1 == Axis::None || target1 == Axis::None);
	for (unsigned int f = 0; f < 4; f++)
	{
		for (unsigned int d = 0; d < 6; d++)
		{
			orient.make(diags[d], flips[f]);
			if ((ignore0 || orient.absolute(origin0) == target0) &&
				(ignore1 || orient.absolute(origin1) == target1))
			{
				*this = orient;
				return;
			}
		}
	}
	*this = VoxelOrientation();
}



VectorF3 VoxelOrientation::absolute(VectorF3 v) const
{
	switch (GetDiag())
	{
		case Diag::Here : v = VectorF3(v.X, v.Y, v.Z); break;
		case Diag::Prev : v = VectorF3(v.Z, v.X, v.Y); break;
		case Diag::Next : v = VectorF3(v.Y, v.Z, v.X); break;
		case Diag::DiagX: v = VectorF3(1 - v.X, 1 - v.Z, 1 - v.Y); break;
		case Diag::DiagY: v = VectorF3(1 - v.Z, 1 - v.Y, 1 - v.X); break;
		case Diag::DiagZ: v = VectorF3(1 - v.Y, 1 - v.X, 1 - v.Z); break;
	}

	switch (GetFlip())
	{
		case Flip::None : v = VectorF3(0 + v.X, 0 + v.Y, 0 + v.Z); break;
		case Flip::FlipX: v = VectorF3(0 + v.X, 1 - v.Y, 1 - v.Z); break;
		case Flip::FlipY: v = VectorF3(1 - v.X, 0 + v.Y, 1 - v.Z); break;
		case Flip::FlipZ: v = VectorF3(1 - v.X, 1 - v.Y, 0 + v.Z); break;
	}

	return v;
}





Axis VoxelOrientation::absolute(Axis axis) const
{
	switch (GetDiag())
	{
		case Diag::Here: switch (axis)
		{
			case Axis::PrevX: axis = Axis::PrevX; break;
			case Axis::PrevY: axis = Axis::PrevY; break;
			case Axis::PrevZ: axis = Axis::PrevZ; break;
			case Axis::NextX: axis = Axis::NextX; break;
			case Axis::NextY: axis = Axis::NextY; break;
			case Axis::NextZ: axis = Axis::NextZ; break;
			default: break;
		} break;
		case Diag::Prev: switch (axis)
		{
			case Axis::PrevX: axis = Axis::PrevY; break;
			case Axis::PrevY: axis = Axis::PrevZ; break;
			case Axis::PrevZ: axis = Axis::PrevX; break;
			case Axis::NextX: axis = Axis::NextY; break;
			case Axis::NextY: axis = Axis::NextZ; break;
			case Axis::NextZ: axis = Axis::NextX; break;
			default: break;
		} break;
		case Diag::Next: switch (axis)
		{
			case Axis::PrevX: axis = Axis::PrevZ; break;
			case Axis::PrevY: axis = Axis::PrevX; break;
			case Axis::PrevZ: axis = Axis::PrevY; break;
			case Axis::NextX: axis = Axis::NextZ; break;
			case Axis::NextY: axis = Axis::NextX; break;
			case Axis::NextZ: axis = Axis::NextY; break;
			default: break;
		} break;
		case Diag::DiagX: switch (axis)
		{
			case Axis::PrevX: axis = Axis::NextX; break;
			case Axis::PrevY: axis = Axis::NextZ; break;
			case Axis::PrevZ: axis = Axis::NextY; break;
			case Axis::NextX: axis = Axis::PrevX; break;
			case Axis::NextY: axis = Axis::PrevZ; break;
			case Axis::NextZ: axis = Axis::PrevY; break;
			default: break;
		} break;
		case Diag::DiagY: switch (axis)
		{
			case Axis::PrevX: axis = Axis::NextZ; break;
			case Axis::PrevY: axis = Axis::NextY; break;
			case Axis::PrevZ: axis = Axis::NextX; break;
			case Axis::NextX: axis = Axis::PrevZ; break;
			case Axis::NextY: axis = Axis::PrevY; break;
			case Axis::NextZ: axis = Axis::PrevX; break;
			default: break;
		} break;
		case Diag::DiagZ: switch (axis)
		{
			case Axis::PrevX: axis = Axis::NextY; break;
			case Axis::PrevY: axis = Axis::NextX; break;
			case Axis::PrevZ: axis = Axis::NextZ; break;
			case Axis::NextX: axis = Axis::PrevY; break;
			case Axis::NextY: axis = Axis::PrevX; break;
			case Axis::NextZ: axis = Axis::PrevZ; break;
			default: break;
		} break;
	}

	switch (GetFlip())
	{
		case Flip::None: switch (axis)
		{
			case Axis::PrevX: axis = Axis::PrevX; break;
			case Axis::PrevY: axis = Axis::PrevY; break;
			case Axis::PrevZ: axis = Axis::PrevZ; break;
			case Axis::NextX: axis = Axis::NextX; break;
			case Axis::NextY: axis = Axis::NextY; break;
			case Axis::NextZ: axis = Axis::NextZ; break;
			default: break;
		} break;
		case Flip::FlipX: switch (axis)
		{
			case Axis::PrevX: axis = Axis::PrevX; break;
			case Axis::PrevY: axis = Axis::NextY; break;
			case Axis::PrevZ: axis = Axis::NextZ; break;
			case Axis::NextX: axis = Axis::NextX; break;
			case Axis::NextY: axis = Axis::PrevY; break;
			case Axis::NextZ: axis = Axis::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipY: switch (axis)
		{
			case Axis::PrevX: axis = Axis::NextX; break;
			case Axis::PrevY: axis = Axis::PrevY; break;
			case Axis::PrevZ: axis = Axis::NextZ; break;
			case Axis::NextX: axis = Axis::PrevX; break;
			case Axis::NextY: axis = Axis::NextY; break;
			case Axis::NextZ: axis = Axis::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipZ: switch (axis)
		{
			case Axis::PrevX: axis = Axis::NextX; break;
			case Axis::PrevY: axis = Axis::NextY; break;
			case Axis::PrevZ: axis = Axis::PrevZ; break;
			case Axis::NextX: axis = Axis::PrevX; break;
			case Axis::NextY: axis = Axis::PrevY; break;
			case Axis::NextZ: axis = Axis::NextZ; break;
			default: break;
		} break;
	}

	return axis;
}
Axis VoxelOrientation::relative(Axis axis) const
{
	switch (GetFlip())
	{
		case Flip::None: switch (axis)
		{
			case Axis::PrevX: axis = Axis::PrevX; break;
			case Axis::PrevY: axis = Axis::PrevY; break;
			case Axis::PrevZ: axis = Axis::PrevZ; break;
			case Axis::NextX: axis = Axis::NextX; break;
			case Axis::NextY: axis = Axis::NextY; break;
			case Axis::NextZ: axis = Axis::NextZ; break;
			default: break;
		} break;
		case Flip::FlipX: switch (axis)
		{
			case Axis::PrevX: axis = Axis::PrevX; break;
			case Axis::PrevY: axis = Axis::NextY; break;
			case Axis::PrevZ: axis = Axis::NextZ; break;
			case Axis::NextX: axis = Axis::NextX; break;
			case Axis::NextY: axis = Axis::PrevY; break;
			case Axis::NextZ: axis = Axis::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipY: switch (axis)
		{
			case Axis::PrevX: axis = Axis::NextX; break;
			case Axis::PrevY: axis = Axis::PrevY; break;
			case Axis::PrevZ: axis = Axis::NextZ; break;
			case Axis::NextX: axis = Axis::PrevX; break;
			case Axis::NextY: axis = Axis::NextY; break;
			case Axis::NextZ: axis = Axis::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipZ: switch (axis)
		{
			case Axis::PrevX: axis = Axis::NextX; break;
			case Axis::PrevY: axis = Axis::NextY; break;
			case Axis::PrevZ: axis = Axis::PrevZ; break;
			case Axis::NextX: axis = Axis::PrevX; break;
			case Axis::NextY: axis = Axis::PrevY; break;
			case Axis::NextZ: axis = Axis::NextZ; break;
			default: break;
		} break;
	}

	switch (GetDiag())
	{
		case Diag::Here: switch (axis)
		{
			case Axis::PrevX: axis = Axis::PrevX; break;
			case Axis::PrevY: axis = Axis::PrevY; break;
			case Axis::PrevZ: axis = Axis::PrevZ; break;
			case Axis::NextX: axis = Axis::NextX; break;
			case Axis::NextY: axis = Axis::NextY; break;
			case Axis::NextZ: axis = Axis::NextZ; break;
			default: break;
		} break;
		case Diag::Prev: switch (axis)
		{
			case Axis::PrevX: axis = Axis::PrevZ; break;
			case Axis::PrevY: axis = Axis::PrevX; break;
			case Axis::PrevZ: axis = Axis::PrevY; break;
			case Axis::NextX: axis = Axis::NextZ; break;
			case Axis::NextY: axis = Axis::NextX; break;
			case Axis::NextZ: axis = Axis::NextY; break;
			default: break;
		} break;
		case Diag::Next: switch (axis)
		{
			case Axis::PrevX: axis = Axis::PrevY; break;
			case Axis::PrevY: axis = Axis::PrevZ; break;
			case Axis::PrevZ: axis = Axis::PrevX; break;
			case Axis::NextX: axis = Axis::NextY; break;
			case Axis::NextY: axis = Axis::NextZ; break;
			case Axis::NextZ: axis = Axis::NextX; break;
			default: break;
		} break;
		case Diag::DiagX: switch (axis)
		{
			case Axis::PrevX: axis = Axis::NextX; break;
			case Axis::PrevY: axis = Axis::NextZ; break;
			case Axis::PrevZ: axis = Axis::NextY; break;
			case Axis::NextX: axis = Axis::PrevX; break;
			case Axis::NextY: axis = Axis::PrevZ; break;
			case Axis::NextZ: axis = Axis::PrevY; break;
			default: break;
		} break;
		case Diag::DiagY: switch (axis)
		{
			case Axis::PrevX: axis = Axis::NextZ; break;
			case Axis::PrevY: axis = Axis::NextY; break;
			case Axis::PrevZ: axis = Axis::NextX; break;
			case Axis::NextX: axis = Axis::PrevZ; break;
			case Axis::NextY: axis = Axis::PrevY; break;
			case Axis::NextZ: axis = Axis::PrevX; break;
			default: break;
		} break;
		case Diag::DiagZ: switch (axis)
		{
			case Axis::PrevX: axis = Axis::NextY; break;
			case Axis::PrevY: axis = Axis::NextX; break;
			case Axis::PrevZ: axis = Axis::NextZ; break;
			case Axis::NextX: axis = Axis::PrevY; break;
			case Axis::NextY: axis = Axis::PrevX; break;
			case Axis::NextZ: axis = Axis::PrevZ; break;
			default: break;
		} break;
	}

	return axis;
}

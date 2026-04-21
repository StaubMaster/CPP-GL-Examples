#include "VoxelOrientation.hpp"



Diag VoxelOrientation::GetDiag() const { return (Diag)((Value & 0b00000111) >> 0); }
Flip VoxelOrientation::GetFlip() const { return (Flip)((Value & 0b00011000) >> 3); }

void VoxelOrientation::SetDiag(Diag diag) { Value = (Value & (~0b00000111)) | (((unsigned char)diag) << 0); }
void VoxelOrientation::SetFlip(Flip flip) { Value = (Value & (~0b00011000)) | (((unsigned char)flip) << 3); }



VoxelOrientation::~VoxelOrientation() { }
VoxelOrientation::VoxelOrientation()
	: Value(0)
{ }

VoxelOrientation::VoxelOrientation(const VoxelOrientation & other)
	: Value(other.Value)
{ }
VoxelOrientation & VoxelOrientation::operator=(const VoxelOrientation & other)
{
	Value = other.Value;
	return *this;
}



void VoxelOrientation::make(Diag diag, Flip flip) { SetDiag(diag); SetFlip(flip); }

void VoxelOrientation::make(AxisRel origin, AxisRel target)
{
	make(origin, target, AxisRel::None, AxisRel::None);
}
void VoxelOrientation::make(AxisRel origin0, AxisRel target0, AxisRel origin1, AxisRel target1)
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

	bool ignore0 = (origin0 == AxisRel::None || target0 == AxisRel::None);
	bool ignore1 = (origin1 == AxisRel::None || target1 == AxisRel::None);
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

AxisRel VoxelOrientation::absolute(AxisRel axis) const
{
	switch (GetDiag())
	{
		case Diag::Here: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::PrevX; break;
			case AxisRel::PrevY: axis = AxisRel::PrevY; break;
			case AxisRel::PrevZ: axis = AxisRel::PrevZ; break;
			case AxisRel::NextX: axis = AxisRel::NextX; break;
			case AxisRel::NextY: axis = AxisRel::NextY; break;
			case AxisRel::NextZ: axis = AxisRel::NextZ; break;
			default: break;
		} break;
		case Diag::Prev: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::PrevY; break;
			case AxisRel::PrevY: axis = AxisRel::PrevZ; break;
			case AxisRel::PrevZ: axis = AxisRel::PrevX; break;
			case AxisRel::NextX: axis = AxisRel::NextY; break;
			case AxisRel::NextY: axis = AxisRel::NextZ; break;
			case AxisRel::NextZ: axis = AxisRel::NextX; break;
			default: break;
		} break;
		case Diag::Next: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::PrevZ; break;
			case AxisRel::PrevY: axis = AxisRel::PrevX; break;
			case AxisRel::PrevZ: axis = AxisRel::PrevY; break;
			case AxisRel::NextX: axis = AxisRel::NextZ; break;
			case AxisRel::NextY: axis = AxisRel::NextX; break;
			case AxisRel::NextZ: axis = AxisRel::NextY; break;
			default: break;
		} break;
		case Diag::DiagX: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::NextX; break;
			case AxisRel::PrevY: axis = AxisRel::NextZ; break;
			case AxisRel::PrevZ: axis = AxisRel::NextY; break;
			case AxisRel::NextX: axis = AxisRel::PrevX; break;
			case AxisRel::NextY: axis = AxisRel::PrevZ; break;
			case AxisRel::NextZ: axis = AxisRel::PrevY; break;
			default: break;
		} break;
		case Diag::DiagY: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::NextZ; break;
			case AxisRel::PrevY: axis = AxisRel::NextY; break;
			case AxisRel::PrevZ: axis = AxisRel::NextX; break;
			case AxisRel::NextX: axis = AxisRel::PrevZ; break;
			case AxisRel::NextY: axis = AxisRel::PrevY; break;
			case AxisRel::NextZ: axis = AxisRel::PrevX; break;
			default: break;
		} break;
		case Diag::DiagZ: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::NextY; break;
			case AxisRel::PrevY: axis = AxisRel::NextX; break;
			case AxisRel::PrevZ: axis = AxisRel::NextZ; break;
			case AxisRel::NextX: axis = AxisRel::PrevY; break;
			case AxisRel::NextY: axis = AxisRel::PrevX; break;
			case AxisRel::NextZ: axis = AxisRel::PrevZ; break;
			default: break;
		} break;
	}

	switch (GetFlip())
	{
		case Flip::None: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::PrevX; break;
			case AxisRel::PrevY: axis = AxisRel::PrevY; break;
			case AxisRel::PrevZ: axis = AxisRel::PrevZ; break;
			case AxisRel::NextX: axis = AxisRel::NextX; break;
			case AxisRel::NextY: axis = AxisRel::NextY; break;
			case AxisRel::NextZ: axis = AxisRel::NextZ; break;
			default: break;
		} break;
		case Flip::FlipX: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::PrevX; break;
			case AxisRel::PrevY: axis = AxisRel::NextY; break;
			case AxisRel::PrevZ: axis = AxisRel::NextZ; break;
			case AxisRel::NextX: axis = AxisRel::NextX; break;
			case AxisRel::NextY: axis = AxisRel::PrevY; break;
			case AxisRel::NextZ: axis = AxisRel::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipY: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::NextX; break;
			case AxisRel::PrevY: axis = AxisRel::PrevY; break;
			case AxisRel::PrevZ: axis = AxisRel::NextZ; break;
			case AxisRel::NextX: axis = AxisRel::PrevX; break;
			case AxisRel::NextY: axis = AxisRel::NextY; break;
			case AxisRel::NextZ: axis = AxisRel::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipZ: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::NextX; break;
			case AxisRel::PrevY: axis = AxisRel::NextY; break;
			case AxisRel::PrevZ: axis = AxisRel::PrevZ; break;
			case AxisRel::NextX: axis = AxisRel::PrevX; break;
			case AxisRel::NextY: axis = AxisRel::PrevY; break;
			case AxisRel::NextZ: axis = AxisRel::NextZ; break;
			default: break;
		} break;
	}

	return axis;
}
AxisRel VoxelOrientation::relative(AxisRel axis) const
{
	switch (GetFlip())
	{
		case Flip::None: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::PrevX; break;
			case AxisRel::PrevY: axis = AxisRel::PrevY; break;
			case AxisRel::PrevZ: axis = AxisRel::PrevZ; break;
			case AxisRel::NextX: axis = AxisRel::NextX; break;
			case AxisRel::NextY: axis = AxisRel::NextY; break;
			case AxisRel::NextZ: axis = AxisRel::NextZ; break;
			default: break;
		} break;
		case Flip::FlipX: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::PrevX; break;
			case AxisRel::PrevY: axis = AxisRel::NextY; break;
			case AxisRel::PrevZ: axis = AxisRel::NextZ; break;
			case AxisRel::NextX: axis = AxisRel::NextX; break;
			case AxisRel::NextY: axis = AxisRel::PrevY; break;
			case AxisRel::NextZ: axis = AxisRel::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipY: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::NextX; break;
			case AxisRel::PrevY: axis = AxisRel::PrevY; break;
			case AxisRel::PrevZ: axis = AxisRel::NextZ; break;
			case AxisRel::NextX: axis = AxisRel::PrevX; break;
			case AxisRel::NextY: axis = AxisRel::NextY; break;
			case AxisRel::NextZ: axis = AxisRel::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipZ: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::NextX; break;
			case AxisRel::PrevY: axis = AxisRel::NextY; break;
			case AxisRel::PrevZ: axis = AxisRel::PrevZ; break;
			case AxisRel::NextX: axis = AxisRel::PrevX; break;
			case AxisRel::NextY: axis = AxisRel::PrevY; break;
			case AxisRel::NextZ: axis = AxisRel::NextZ; break;
			default: break;
		} break;
	}

	switch (GetDiag())
	{
		case Diag::Here: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::PrevX; break;
			case AxisRel::PrevY: axis = AxisRel::PrevY; break;
			case AxisRel::PrevZ: axis = AxisRel::PrevZ; break;
			case AxisRel::NextX: axis = AxisRel::NextX; break;
			case AxisRel::NextY: axis = AxisRel::NextY; break;
			case AxisRel::NextZ: axis = AxisRel::NextZ; break;
			default: break;
		} break;
		case Diag::Prev: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::PrevZ; break;
			case AxisRel::PrevY: axis = AxisRel::PrevX; break;
			case AxisRel::PrevZ: axis = AxisRel::PrevY; break;
			case AxisRel::NextX: axis = AxisRel::NextZ; break;
			case AxisRel::NextY: axis = AxisRel::NextX; break;
			case AxisRel::NextZ: axis = AxisRel::NextY; break;
			default: break;
		} break;
		case Diag::Next: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::PrevY; break;
			case AxisRel::PrevY: axis = AxisRel::PrevZ; break;
			case AxisRel::PrevZ: axis = AxisRel::PrevX; break;
			case AxisRel::NextX: axis = AxisRel::NextY; break;
			case AxisRel::NextY: axis = AxisRel::NextZ; break;
			case AxisRel::NextZ: axis = AxisRel::NextX; break;
			default: break;
		} break;
		case Diag::DiagX: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::NextX; break;
			case AxisRel::PrevY: axis = AxisRel::NextZ; break;
			case AxisRel::PrevZ: axis = AxisRel::NextY; break;
			case AxisRel::NextX: axis = AxisRel::PrevX; break;
			case AxisRel::NextY: axis = AxisRel::PrevZ; break;
			case AxisRel::NextZ: axis = AxisRel::PrevY; break;
			default: break;
		} break;
		case Diag::DiagY: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::NextZ; break;
			case AxisRel::PrevY: axis = AxisRel::NextY; break;
			case AxisRel::PrevZ: axis = AxisRel::NextX; break;
			case AxisRel::NextX: axis = AxisRel::PrevZ; break;
			case AxisRel::NextY: axis = AxisRel::PrevY; break;
			case AxisRel::NextZ: axis = AxisRel::PrevX; break;
			default: break;
		} break;
		case Diag::DiagZ: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::NextY; break;
			case AxisRel::PrevY: axis = AxisRel::NextX; break;
			case AxisRel::PrevZ: axis = AxisRel::NextZ; break;
			case AxisRel::NextX: axis = AxisRel::PrevY; break;
			case AxisRel::NextY: axis = AxisRel::PrevX; break;
			case AxisRel::NextZ: axis = AxisRel::PrevZ; break;
			default: break;
		} break;
	}

	return axis;
}

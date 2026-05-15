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

/* absolute Swizzles
00 Here  None  (+X, +Y, +Z) (+X, +Y, +Z) : (+X, +Y, +Z)
01 Next  None  (+Y, +Z, +X) (+X, +Y, +Z) : (+Y, +Z, +X)
02 Prev  None  (+Z, +X, +Y) (+X, +Y, +Z) : (+Z, +X, +Y)
03 DiagX None  (-X, -Z, -Y) (+X, +Y, +Z) : (-X, -Z, -Y)
04 DiagY None  (-Z, -Y, -X) (+X, +Y, +Z) : (-Z, -Y, -X)
05 DiagZ None  (-Y, -X, -Z) (+X, +Y, +Z) : (-Y, -X, -Z)
08 Here  FlipX (+X, +Y, +Z) (+X, -Y, -Z) : (+X, -Y, -Z)
09 Next  FlipX (+Y, +Z, +X) (+X, -Y, -Z) : (+Y, -Z, -X)
10 Prev  FlipX (+Z, +X, +Y) (+X, -Y, -Z) : (+Z, -X, -Y)
11 DiagX FlipX (-X, -Z, -Y) (+X, -Y, -Z) : (-X, +Z, +Y)
12 DiagY FlipX (-Z, -Y, -X) (+X, -Y, -Z) : (-Z, +Y, +X)
13 DiagZ FlipX (-Y, -X, -Z) (+X, -Y, -Z) : (-Y, +X, +Z)
16 Here  FlipY (+X, +Y, +Z) (-X, +Y, -Z) : (-X, +Y, -Z)
17 Next  FlipY (+Y, +Z, +X) (-X, +Y, -Z) : (-Y, +Z, -X)
18 Prev  FlipY (+Z, +X, +Y) (-X, +Y, -Z) : (-Z, +X, -Y)
19 DiagX FlipY (-X, -Z, -Y) (-X, +Y, -Z) : (+X, -Z, +Y)
20 DiagY FlipY (-Z, -Y, -X) (-X, +Y, -Z) : (+Z, -Y, +X)
21 DiagZ FlipY (-Y, -X, -Z) (-X, +Y, -Z) : (+Y, -X, +Z)
24 Here  FlipZ (+X, +Y, +Z) (-X, -Y, +Z) : (-X, -Y, +Z)
25 Next  FlipZ (+Y, +Z, +X) (-X, -Y, +Z) : (-Y, -Z, +X)
26 Prev  FlipZ (+Z, +X, +Y) (-X, -Y, +Z) : (-Z, -X, +Y)
27 DiagX FlipZ (-X, -Z, -Y) (-X, -Y, +Z) : (+X, +Z, -Y)
28 DiagY FlipZ (-Z, -Y, -X) (-X, -Y, +Z) : (+Z, +Y, -X)
29 DiagZ FlipZ (-Y, -X, -Z) (-X, -Y, +Z) : (+Y, +X, -Z)
*/

/* [32]
[00] (+X, +Y, +Z)
[01] (+Y, +Z, +X)
[02] (+Z, +X, +Y)
[03] (-X, -Z, -Y)
[04] (-Z, -Y, -X)
[05] (-Y, -X, -Z)
[06]
[07]
[08] (+X, -Y, -Z)
[09] (+Y, -Z, -X)
[10] (+Z, -X, -Y)
[11] (-X, +Z, +Y)
[12] (-Z, +Y, +X)
[13] (-Y, +X, +Z)
[14]
[15]
[16] (-X, +Y, -Z)
[17] (-Y, +Z, -X)
[18] (-Z, +X, -Y)
[19] (+X, -Z, +Y)
[20] (+Z, -Y, +X)
[21] (+Y, -X, +Z)
[22]
[23]
[24] (-X, -Y, +Z)
[25] (-Y, -Z, +X)
[26] (-Z, -X, +Y)
[27] (+X, +Z, -Y)
[28] (+Z, +Y, -X)
[29] (+Y, +X, -Z)
[30]
[31]
*/

VectorU3 absoluteU_SwizzleFunc_00(const VectorU3 & u) { return VectorU3(+u.X, +u.Y, +u.Z); }
VectorU3 absoluteU_SwizzleFunc_01(const VectorU3 & u) { return VectorU3(+u.X, +u.Y, +u.Z); }
VectorU3 absoluteU_SwizzleFunc_02(const VectorU3 & u) { return VectorU3(+u.X, +u.Y, +u.Z); }
VectorU3 absoluteU_SwizzleFunc_03(const VectorU3 & u) { return VectorU3(+u.X, +u.Y, +u.Z); }
VectorU3 absoluteU_SwizzleFunc_04(const VectorU3 & u) { return VectorU3(+u.X, +u.Y, +u.Z); }
VectorU3 absoluteU_SwizzleFunc_05(const VectorU3 & u) { return VectorU3(+u.X, +u.Y, +u.Z); }

VectorU3 absoluteU_SwizzleFunc_08(const VectorU3 & u) { return VectorU3(+u.X, -u.Y, -u.Z); }
VectorU3 absoluteU_SwizzleFunc_09(const VectorU3 & u) { return VectorU3(+u.Y, -u.Z, -u.X); }
VectorU3 absoluteU_SwizzleFunc_10(const VectorU3 & u) { return VectorU3(+u.Z, -u.X, -u.Y); }
VectorU3 absoluteU_SwizzleFunc_11(const VectorU3 & u) { return VectorU3(-u.X, +u.Z, +u.Y); }
VectorU3 absoluteU_SwizzleFunc_12(const VectorU3 & u) { return VectorU3(-u.Z, +u.Y, +u.X); }
VectorU3 absoluteU_SwizzleFunc_13(const VectorU3 & u) { return VectorU3(-u.Y, +u.X, +u.Z); }

VectorU3 absoluteU_SwizzleFunc_16(const VectorU3 & u) { return VectorU3(-u.X, +u.Y, -u.Z); }
VectorU3 absoluteU_SwizzleFunc_17(const VectorU3 & u) { return VectorU3(-u.Y, +u.Z, -u.X); }
VectorU3 absoluteU_SwizzleFunc_18(const VectorU3 & u) { return VectorU3(-u.Z, +u.X, -u.Y); }
VectorU3 absoluteU_SwizzleFunc_19(const VectorU3 & u) { return VectorU3(+u.X, -u.Z, +u.Y); }
VectorU3 absoluteU_SwizzleFunc_20(const VectorU3 & u) { return VectorU3(+u.Z, -u.Y, +u.X); }
VectorU3 absoluteU_SwizzleFunc_21(const VectorU3 & u) { return VectorU3(+u.Y, -u.X, +u.Z); }

VectorU3 absoluteU_SwizzleFunc_24(const VectorU3 & u) { return VectorU3(-u.X, -u.Y, +u.Z); }
VectorU3 absoluteU_SwizzleFunc_25(const VectorU3 & u) { return VectorU3(-u.Y, -u.Z, +u.X); }
VectorU3 absoluteU_SwizzleFunc_26(const VectorU3 & u) { return VectorU3(-u.Z, -u.X, +u.Y); }
VectorU3 absoluteU_SwizzleFunc_27(const VectorU3 & u) { return VectorU3(+u.X, +u.Z, -u.Y); }
VectorU3 absoluteU_SwizzleFunc_28(const VectorU3 & u) { return VectorU3(+u.Z, +u.Y, -u.X); }
VectorU3 absoluteU_SwizzleFunc_29(const VectorU3 & u) { return VectorU3(+u.Y, +u.X, -u.Z); }

VoxelOrientation::SwizzlerU_Ptr absoluteU_SwizzleFunc_Array[32] = {
	&absoluteU_SwizzleFunc_00,
	&absoluteU_SwizzleFunc_01,
	&absoluteU_SwizzleFunc_02,
	&absoluteU_SwizzleFunc_03,
	&absoluteU_SwizzleFunc_04,
	&absoluteU_SwizzleFunc_05,
	nullptr,
	nullptr,
	&absoluteU_SwizzleFunc_08,
	&absoluteU_SwizzleFunc_09,
	&absoluteU_SwizzleFunc_10,
	&absoluteU_SwizzleFunc_11,
	&absoluteU_SwizzleFunc_12,
	&absoluteU_SwizzleFunc_13,
	nullptr,
	nullptr,
	&absoluteU_SwizzleFunc_16,
	&absoluteU_SwizzleFunc_17,
	&absoluteU_SwizzleFunc_18,
	&absoluteU_SwizzleFunc_19,
	&absoluteU_SwizzleFunc_20,
	&absoluteU_SwizzleFunc_21,
	nullptr,
	nullptr,
	&absoluteU_SwizzleFunc_24,
	&absoluteU_SwizzleFunc_25,
	&absoluteU_SwizzleFunc_26,
	&absoluteU_SwizzleFunc_27,
	&absoluteU_SwizzleFunc_28,
	&absoluteU_SwizzleFunc_29,
	nullptr,
	nullptr
};

VoxelOrientation::SwizzlerU_Ref VoxelOrientation::absoluteU_Func() const { return *(absoluteU_SwizzleFunc_Array[Value]); }



VectorU3 VoxelOrientation::absolute(VectorU3 v) const
{
	switch (GetDiag())
	{
		case Diag::Here : v = VectorU3(v.X, v.Y, v.Z); break;
		case Diag::Prev : v = VectorU3(v.Z, v.X, v.Y); break;
		case Diag::Next : v = VectorU3(v.Y, v.Z, v.X); break;
		case Diag::DiagX: v = VectorU3(1 - v.X, 1 - v.Z, 1 - v.Y); break;
		case Diag::DiagY: v = VectorU3(1 - v.Z, 1 - v.Y, 1 - v.X); break;
		case Diag::DiagZ: v = VectorU3(1 - v.Y, 1 - v.X, 1 - v.Z); break;
	}

	switch (GetFlip())
	{
		case Flip::None : v = VectorU3(0 + v.X, 0 + v.Y, 0 + v.Z); break;
		case Flip::FlipX: v = VectorU3(0 + v.X, 1 - v.Y, 1 - v.Z); break;
		case Flip::FlipY: v = VectorU3(1 - v.X, 0 + v.Y, 1 - v.Z); break;
		case Flip::FlipZ: v = VectorU3(1 - v.X, 1 - v.Y, 0 + v.Z); break;
	}

	return v;
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

/* optimize this into functions ?
did I half solve this already ?

PrevX to NextX is inverting the Bits
PrevX to PrevY is rotate left
PrevX to PrevZ is rotate right

rotate only the lowest 3 bits

*/

AxisRel VoxelOrientation::absolute(AxisRel axis) const
{
	switch (GetDiag())
	{
		case Diag::Here: switch (axis)
		{
			//case AxisRel::PrevX: axis = AxisRel::PrevX; break;
			//case AxisRel::PrevY: axis = AxisRel::PrevY; break;
			//case AxisRel::PrevZ: axis = AxisRel::PrevZ; break;
			//case AxisRel::NextX: axis = AxisRel::NextX; break;
			//case AxisRel::NextY: axis = AxisRel::NextY; break;
			//case AxisRel::NextZ: axis = AxisRel::NextZ; break;
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
			case AxisRel::PrevX: axis = AxisRel::NextX; break; // PrevX(001)  ~  NextX(110)
			case AxisRel::PrevY: axis = AxisRel::NextZ; break; // PrevY(010) <<~ NextZ(011)
			case AxisRel::PrevZ: axis = AxisRel::NextY; break; // PrevZ(100) ~>> NextY(101)
			case AxisRel::NextX: axis = AxisRel::PrevX; break; // NextX(110)  ~  PrevX(001)
			case AxisRel::NextY: axis = AxisRel::PrevZ; break; // NextY(101) <<~ PrevZ(100)
			case AxisRel::NextZ: axis = AxisRel::PrevY; break; // NextZ(011) ~>> PrevY(010)
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
			//case AxisRel::PrevX: axis = AxisRel::PrevX; break;
			//case AxisRel::PrevY: axis = AxisRel::PrevY; break;
			//case AxisRel::PrevZ: axis = AxisRel::PrevZ; break;
			//case AxisRel::NextX: axis = AxisRel::NextX; break;
			//case AxisRel::NextY: axis = AxisRel::NextY; break;
			//case AxisRel::NextZ: axis = AxisRel::NextZ; break;
			default: break;
		} break;
		case Flip::FlipX: switch (axis)
		{
			//case AxisRel::PrevX: axis = AxisRel::PrevX; break;
			case AxisRel::PrevY: axis = AxisRel::NextY; break;
			case AxisRel::PrevZ: axis = AxisRel::NextZ; break;
			//case AxisRel::NextX: axis = AxisRel::NextX; break;
			case AxisRel::NextY: axis = AxisRel::PrevY; break;
			case AxisRel::NextZ: axis = AxisRel::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipY: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::NextX; break;
			//case AxisRel::PrevY: axis = AxisRel::PrevY; break;
			case AxisRel::PrevZ: axis = AxisRel::NextZ; break;
			case AxisRel::NextX: axis = AxisRel::PrevX; break;
			//case AxisRel::NextY: axis = AxisRel::NextY; break;
			case AxisRel::NextZ: axis = AxisRel::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipZ: switch (axis)
		{
			case AxisRel::PrevX: axis = AxisRel::NextX; break;
			case AxisRel::PrevY: axis = AxisRel::NextY; break;
			//case AxisRel::PrevZ: axis = AxisRel::PrevZ; break;
			case AxisRel::NextX: axis = AxisRel::PrevX; break;
			case AxisRel::NextY: axis = AxisRel::PrevY; break;
			//case AxisRel::NextZ: axis = AxisRel::NextZ; break;
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

#include "Orientation.hpp"
#include "Enums.hpp"

#include "ValueType/Vector/F2.hpp"
#include "ValueType/Vector/U2.hpp"



Axis2D::Diag Axis2D::Orientation::GetDiag() const { return (Axis2D::Diag)((Value & 0b00000011) >> 0); }
Axis2D::Flip Axis2D::Orientation::GetFlip() const { return (Axis2D::Flip)((Value & 0b00001100) >> 2); }

void Axis2D::Orientation::SetDiag(Axis2D::Diag diag) { Value = (Value & (~0b00000011)) | (((unsigned char)diag) << 0); }
void Axis2D::Orientation::SetFlip(Axis2D::Flip flip) { Value = (Value & (~0b00001100)) | (((unsigned char)flip) << 2); }



Axis2D::Orientation::Orientation(Diag diag, Flip flip)
{
	SetDiag(diag);
	SetFlip(flip);
}



/*static Axis2D::Rel s_absolute(const Axis2D::Diag & diag, const Axis2D::Rel & axis)
{
	switch (diag)
	{
		case Axis2D::Diag::Here: switch (axis)
		{
		//	case Axis2D::Rel::PrevX: axis = Axis2D::Rel::PrevX; break;
		//	case Axis2D::Rel::PrevY: axis = Axis2D::Rel::PrevY; break;
		//	case Axis2D::Rel::PrevZ: axis = Axis2D::Rel::PrevZ; break;
		//	case Axis2D::Rel::NextX: axis = Axis2D::Rel::NextX; break;
		//	case Axis2D::Rel::NextY: axis = Axis2D::Rel::NextY; break;
		//	case Axis2D::Rel::NextZ: axis = Axis2D::Rel::NextZ; break;
			default: break;
		} break;
		case Axis2D::Diag::Prev: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::PrevZ;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::NextX: return Axis2D::Rel::NextY;
			case Axis2D::Rel::NextY: return Axis2D::Rel::NextZ;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::NextX;
			default: break;
		} break;
		case Axis2D::Diag::Next: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::PrevZ;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::NextX: return Axis2D::Rel::NextZ;
			case Axis2D::Rel::NextY: return Axis2D::Rel::NextX;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::NextY;
			default: break;
		} break;
		case Axis2D::Diag::DiagX: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::NextX; // PrevX(001)  ~  NextX(110)
			case Axis2D::Rel::PrevY: return Axis2D::Rel::NextZ; // PrevY(010) <<~ NextZ(011)
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::NextY; // PrevZ(100) ~>> NextY(101)
			case Axis2D::Rel::NextX: return Axis2D::Rel::PrevX; // NextX(110)  ~  PrevX(001)
			case Axis2D::Rel::NextY: return Axis2D::Rel::PrevZ; // NextY(101) <<~ PrevZ(100)
			case Axis2D::Rel::NextZ: return Axis2D::Rel::PrevY; // NextZ(011) ~>> PrevY(010)
			default: break;
		} break;
		case Axis2D::Diag::DiagY: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::NextZ;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::NextY;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::NextX;
			case Axis2D::Rel::NextX: return Axis2D::Rel::PrevZ;
			case Axis2D::Rel::NextY: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::PrevX;
			default: break;
		} break;
		case Axis2D::Diag::DiagZ: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::NextY;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::NextX;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::NextZ;
			case Axis2D::Rel::NextX: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::NextY: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::PrevZ;
			default: break;
		} break;
	}
	return axis;
}*/
/*static Axis2D::Rel s_absolute(const Axis2D::Flip & flip, const Axis2D::Rel & axis)
{
	switch (flip)
	{
		case Axis2D::Flip::None: switch (axis)
		{
		//	case Axis2D::Rel::PrevX: return Axis2D::Rel::PrevX;
		//	case Axis2D::Rel::PrevY: return Axis2D::Rel::PrevY;
		//	case Axis2D::Rel::PrevZ: return Axis2D::Rel::PrevZ;
		//	case Axis2D::Rel::NextX: return Axis2D::Rel::NextX;
		//	case Axis2D::Rel::NextY: return Axis2D::Rel::NextY;
		//	case Axis2D::Rel::NextZ: return Axis2D::Rel::NextZ;
			default: break;
		} break;
		case Axis2D::Flip::FlipX: switch (axis)
		{
		//	case Axis2D::Rel::PrevX: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::NextY;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::NextZ;
		//	case Axis2D::Rel::NextX: return Axis2D::Rel::NextX;
			case Axis2D::Rel::NextY: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::PrevZ;
			default: break;
		} break;
		case Axis2D::Flip::FlipY: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::NextX;
		//	case Axis2D::Rel::PrevY: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::NextZ;
			case Axis2D::Rel::NextX: return Axis2D::Rel::PrevX;
		//	case Axis2D::Rel::NextY: return Axis2D::Rel::NextY;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::PrevZ;
			default: break;
		} break;
		case Axis2D::Flip::FlipZ: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::NextX;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::NextY;
		//	case Axis2D::Rel::PrevZ: return Axis2D::Rel::PrevZ;
			case Axis2D::Rel::NextX: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::NextY: return Axis2D::Rel::PrevY;
		//	case Axis2D::Rel::NextZ: return Axis2D::Rel::NextZ;
			default: break;
		} break;
	}
	return axis;
}*/
/*Axis2D::Rel Axis2D::Orientation::absolute(const Axis2D::Rel & axis) const
{
	return s_absolute(GetFlip(), s_absolute(GetDiag(), axis));
}*/

/*static Axis2D::Rel s_relative(const Axis2D::Diag & diag, const Axis2D::Rel & axis)
{
	switch (diag)
	{
		case Axis2D::Diag::Here: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::PrevZ;
			case Axis2D::Rel::NextX: return Axis2D::Rel::NextX;
			case Axis2D::Rel::NextY: return Axis2D::Rel::NextY;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::NextZ;
			default: break;
		} break;
		case Axis2D::Diag::Prev: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::PrevZ;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::NextX: return Axis2D::Rel::NextZ;
			case Axis2D::Rel::NextY: return Axis2D::Rel::NextX;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::NextY;
			default: break;
		} break;
		case Axis2D::Diag::Next: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::PrevZ;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::NextX: return Axis2D::Rel::NextY;
			case Axis2D::Rel::NextY: return Axis2D::Rel::NextZ;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::NextX;
			default: break;
		} break;
		case Axis2D::Diag::DiagX: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::NextX;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::NextZ;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::NextY;
			case Axis2D::Rel::NextX: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::NextY: return Axis2D::Rel::PrevZ;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::PrevY;
			default: break;
		} break;
		case Axis2D::Diag::DiagY: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::NextZ;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::NextY;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::NextX;
			case Axis2D::Rel::NextX: return Axis2D::Rel::PrevZ;
			case Axis2D::Rel::NextY: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::PrevX;
			default: break;
		} break;
		case Axis2D::Diag::DiagZ: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::NextY;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::NextX;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::NextZ;
			case Axis2D::Rel::NextX: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::NextY: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::PrevZ;
			default: break;
		} break;
	}
	return axis;
}*/
/*static Axis2D::Rel s_relative(const Axis2D::Flip & flip, const Axis2D::Rel & axis)
{
	switch (flip)
	{
		case Axis2D::Flip::None: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::PrevZ;
			case Axis2D::Rel::NextX: return Axis2D::Rel::NextX;
			case Axis2D::Rel::NextY: return Axis2D::Rel::NextY;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::NextZ;
			default: break;
		} break;
		case Axis2D::Flip::FlipX: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::NextY;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::NextZ;
			case Axis2D::Rel::NextX: return Axis2D::Rel::NextX;
			case Axis2D::Rel::NextY: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::PrevZ;
			default: break;
		} break;
		case Axis2D::Flip::FlipY: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::NextX;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::NextZ;
			case Axis2D::Rel::NextX: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::NextY: return Axis2D::Rel::NextY;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::PrevZ;
			default: break;
		} break;
		case Axis2D::Flip::FlipZ: switch (axis)
		{
			case Axis2D::Rel::PrevX: return Axis2D::Rel::NextX;
			case Axis2D::Rel::PrevY: return Axis2D::Rel::NextY;
			case Axis2D::Rel::PrevZ: return Axis2D::Rel::PrevZ;
			case Axis2D::Rel::NextX: return Axis2D::Rel::PrevX;
			case Axis2D::Rel::NextY: return Axis2D::Rel::PrevY;
			case Axis2D::Rel::NextZ: return Axis2D::Rel::NextZ;
			default: break;
		} break;
	}
	return axis;
}*/
/*Axis2D::Rel Axis2D::Orientation::relative(const Axis2D::Rel & axis) const
{
	return s_relative(GetDiag(), s_relative(GetFlip(), axis));
}*/



static VectorU2 s_absolute(const Axis2D::Diag & diag, const VectorU2 & v)
{
	switch (diag)
	{
		case Axis2D::Diag::Normal0: return VectorU2(0 + v.X, 0 + v.Y);
		case Axis2D::Diag::Invert0: return VectorU2(0 + v.Y, 0 + v.X);
		case Axis2D::Diag::Normal1: return VectorU2(1 - v.X, 1 - v.Y);
		case Axis2D::Diag::Invert1: return VectorU2(1 - v.Y, 1 - v.X);
	}
	return v;
}
static VectorU2 s_absolute(const Axis2D::Flip & flip, const VectorU2 & v)
{
	switch (flip)
	{
		case Axis2D::Flip::None : return VectorU2(0 + v.X, 0 + v.Y);
		case Axis2D::Flip::FlipX: return VectorU2(0 + v.X, 1 - v.Y);
		case Axis2D::Flip::FlipY: return VectorU2(1 - v.X, 0 + v.Y);
	}
	return v;
}
VectorU2 Axis2D::Orientation::absolute(const VectorU2 & v) const
{
	return s_absolute(GetFlip(), s_absolute(GetDiag(), v));
}

static VectorF2 s_absolute(const Axis2D::Diag & diag, const VectorF2 & v)
{
	switch (diag)
	{
		case Axis2D::Diag::Normal0: return VectorF2(0.0f + v.X, 0.0f + v.Y);
		case Axis2D::Diag::Invert0: return VectorF2(0.0f + v.Y, 0.0f + v.X);
		case Axis2D::Diag::Normal1: return VectorF2(1.0f - v.X, 1.0f - v.Y);
		case Axis2D::Diag::Invert1: return VectorF2(1.0f - v.Y, 1.0f - v.X);
	}
	return v;
}
static VectorF2 s_absolute(const Axis2D::Flip & flip, const VectorF2 & v)
{
	switch (flip)
	{
		case Axis2D::Flip::None : return VectorF2(0.0f + v.X, 0.0f + v.Y);
		case Axis2D::Flip::FlipX: return VectorF2(0.0f + v.X, 1.0f - v.Y);
		case Axis2D::Flip::FlipY: return VectorF2(1.0f - v.X, 0.0f + v.Y);
	}
	return v;
}
VectorF2 Axis2D::Orientation::absolute(const VectorF2 & v) const
{
	return s_absolute(GetFlip(), s_absolute(GetDiag(), v));
}



/* absolute Swizzles
00 Normal0 None  (+X, +Y) (+X, +Y) : (+X, +Y)
01 Invert0 None  (+Y, +X) (+X, +Y) : (+Y, +X)
02 Normal1 None  (-X, -Y) (+X, +Y) : (-X, -Y)
03 Invert1 None  (-Y, -X) (+X, +Y) : (-Y, -X)
04 Normal0 FlipX (+X, +Y) (+X, -Y) : (+X, -Y)
05 Invert0 FlipX (+Y, +X) (+X, -Y) : (+Y, -X)
06 Normal1 FlipX (-X, -Y) (+X, -Y) : (-X, +Y)
07 Invert1 FlipX (-Y, -X) (+X, -Y) : (-Y, +X)
08 Normal0 FlipY (+X, +Y) (-X, +Y) : (-X, +Y)
09 Invert0 FlipY (+Y, +X) (-X, +Y) : (-Y, +X)
10 Normal1 FlipY (-X, -Y) (-X, +Y) : (+X, -Y)
11 Invert1 FlipY (-Y, -X) (-X, +Y) : (+Y, -X)
there are duplicates */

/*
[00] (+X, +Y)
[01] (+Y, +X)
[02] (-X, -Y)
[03] (-Y, -X)
[04] (+X, -Y)
[05] (+Y, -X)
[06] (-X, +Y)
[07] (-Y, +X)
[08] (-X, +Y)
[09] (-Y, +X)
[10] (+X, -Y)
[11] (+Y, -X)
[12]
[13]
[14]
[15]
*/

static VectorU2 absolute_U2_SwizzleFunc_00(const VectorU2 & u) { return VectorU2(0 + u.X, 0 + u.Y); }
static VectorU2 absolute_U2_SwizzleFunc_01(const VectorU2 & u) { return VectorU2(0 + u.Y, 0 + u.X); }
static VectorU2 absolute_U2_SwizzleFunc_02(const VectorU2 & u) { return VectorU2(1 - u.X, 1 - u.Y); }
static VectorU2 absolute_U2_SwizzleFunc_03(const VectorU2 & u) { return VectorU2(1 - u.Y, 1 - u.X); }

static VectorU2 absolute_U2_SwizzleFunc_04(const VectorU2 & u) { return VectorU2(0 + u.X, 1 - u.Y); }
static VectorU2 absolute_U2_SwizzleFunc_05(const VectorU2 & u) { return VectorU2(0 + u.Y, 1 - u.X); }
static VectorU2 absolute_U2_SwizzleFunc_06(const VectorU2 & u) { return VectorU2(1 - u.X, 0 + u.Y); }
static VectorU2 absolute_U2_SwizzleFunc_07(const VectorU2 & u) { return VectorU2(1 - u.Y, 0 + u.X); }

static VectorU2 absolute_U2_SwizzleFunc_08(const VectorU2 & u) { return VectorU2(1 - u.X, 0 + u.Y); }
static VectorU2 absolute_U2_SwizzleFunc_09(const VectorU2 & u) { return VectorU2(1 - u.Y, 0 + u.X); }
static VectorU2 absolute_U2_SwizzleFunc_10(const VectorU2 & u) { return VectorU2(0 + u.X, 1 - u.Y); }
static VectorU2 absolute_U2_SwizzleFunc_11(const VectorU2 & u) { return VectorU2(0 + u.Y, 1 - u.X); }

Axis2D::Orientation::SwizzlerU_Ptr absolute_U2_SwizzleFunc_Array[16] = {
	&absolute_U2_SwizzleFunc_00,
	&absolute_U2_SwizzleFunc_01,
	&absolute_U2_SwizzleFunc_02,
	&absolute_U2_SwizzleFunc_03,
	&absolute_U2_SwizzleFunc_04,
	&absolute_U2_SwizzleFunc_05,
	&absolute_U2_SwizzleFunc_06,
	&absolute_U2_SwizzleFunc_07,
	&absolute_U2_SwizzleFunc_08,
	&absolute_U2_SwizzleFunc_09,
	&absolute_U2_SwizzleFunc_10,
	&absolute_U2_SwizzleFunc_11,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
};

Axis2D::Orientation::SwizzlerU_Ref Axis2D::Orientation::absolute_U_Func() const
{
	return *(absolute_U2_SwizzleFunc_Array[Value]);
}



static VectorF2 absolute_F2_SwizzleFunc_00(const VectorF2 & u) { return VectorF2(0.0f + u.X, 0.0f + u.Y); }
static VectorF2 absolute_F2_SwizzleFunc_01(const VectorF2 & u) { return VectorF2(0.0f + u.Y, 0.0f + u.X); }
static VectorF2 absolute_F2_SwizzleFunc_02(const VectorF2 & u) { return VectorF2(1.0f - u.X, 1.0f - u.Y); }
static VectorF2 absolute_F2_SwizzleFunc_03(const VectorF2 & u) { return VectorF2(1.0f - u.Y, 1.0f - u.X); }

static VectorF2 absolute_F2_SwizzleFunc_04(const VectorF2 & u) { return VectorF2(0.0f + u.X, 1.0f - u.Y); }
static VectorF2 absolute_F2_SwizzleFunc_05(const VectorF2 & u) { return VectorF2(0.0f + u.Y, 1.0f - u.X); }
static VectorF2 absolute_F2_SwizzleFunc_06(const VectorF2 & u) { return VectorF2(1.0f - u.X, 0.0f + u.Y); }
static VectorF2 absolute_F2_SwizzleFunc_07(const VectorF2 & u) { return VectorF2(1.0f - u.Y, 0.0f + u.X); }

static VectorF2 absolute_F2_SwizzleFunc_08(const VectorF2 & u) { return VectorF2(1.0f - u.X, 0.0f + u.Y); }
static VectorF2 absolute_F2_SwizzleFunc_09(const VectorF2 & u) { return VectorF2(1.0f - u.Y, 0.0f + u.X); }
static VectorF2 absolute_F2_SwizzleFunc_10(const VectorF2 & u) { return VectorF2(0.0f + u.X, 1.0f - u.Y); }
static VectorF2 absolute_F2_SwizzleFunc_11(const VectorF2 & u) { return VectorF2(0.0f + u.Y, 1.0f - u.X); }

Axis2D::Orientation::SwizzlerF_Ptr absolute_F2_SwizzleFunc_Array[16] = {
	&absolute_F2_SwizzleFunc_00,
	&absolute_F2_SwizzleFunc_01,
	&absolute_F2_SwizzleFunc_02,
	&absolute_F2_SwizzleFunc_03,
	&absolute_F2_SwizzleFunc_04,
	&absolute_F2_SwizzleFunc_05,
	&absolute_F2_SwizzleFunc_06,
	&absolute_F2_SwizzleFunc_07,
	&absolute_F2_SwizzleFunc_08,
	&absolute_F2_SwizzleFunc_09,
	&absolute_F2_SwizzleFunc_10,
	&absolute_F2_SwizzleFunc_11,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
};

Axis2D::Orientation::SwizzlerF_Ref Axis2D::Orientation::absolute_F_Func() const
{
	return *(absolute_F2_SwizzleFunc_Array[Value]);
}

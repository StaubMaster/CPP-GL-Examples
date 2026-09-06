#include "Orientation.hpp"
#include "Enums.hpp"

#include "ValueType/Vector/F3.hpp"
#include "ValueType/Vector/U3.hpp"



Axis3D::Diag Axis3D::Orientation::GetDiag() const { return (Axis3D::Diag)((Value & 0b00000111) >> 0); }
Axis3D::Flip Axis3D::Orientation::GetFlip() const { return (Axis3D::Flip)((Value & 0b00011000) >> 3); }

void Axis3D::Orientation::SetDiag(Axis3D::Diag diag) { Value = (Value & (~0b00000111)) | (((unsigned char)diag) << 0); }
void Axis3D::Orientation::SetFlip(Axis3D::Flip flip) { Value = (Value & (~0b00011000)) | (((unsigned char)flip) << 3); }



Axis3D::Orientation::Orientation(Diag diag, Flip flip)
{
	SetDiag(diag);
	SetFlip(flip);
}



void Axis3D::Orientation::make(Axis3D::Rel origin, Axis3D::Rel target)
{
	make(origin, target, Axis3D::Rel::None, Axis3D::Rel::None);
}
void Axis3D::Orientation::make(Axis3D::Rel origin0, Axis3D::Rel target0, Axis3D::Rel origin1, Axis3D::Rel target1)
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
	Axis3D::Orientation orient;

	bool ignore0 = (origin0 == Axis3D::Rel::None || target0 == Axis3D::Rel::None);
	bool ignore1 = (origin1 == Axis3D::Rel::None || target1 == Axis3D::Rel::None);
	for (unsigned int f = 0; f < 4; f++)
	{
		for (unsigned int d = 0; d < 6; d++)
		{
			orient.SetDiag(diags[d]);
			orient.SetFlip(flips[f]);
			if ((ignore0 || orient.absolute(origin0) == target0) &&
				(ignore1 || orient.absolute(origin1) == target1))
			{
				*this = orient;
				return;
			}
		}
	}
	*this = Axis3D::Orientation();
}



/* optimize this into functions ?
did I half solve this already ?

PrevX to NextX is inverting the Bits
PrevX to PrevY is rotate left
PrevX to PrevZ is rotate right

rotate only the lowest 3 bits



PrevX(001)
PrevY(010)
PrevZ(100)
NextX(110)
NextY(101)
NextZ(011)
*/

static Axis3D::Rel s_absolute(const Axis3D::Diag & diag, const Axis3D::Rel & axis)
{
	switch (diag)
	{
		case Axis3D::Diag::Here: switch (axis)
		{
		//	case Axis3D::Rel::PrevX: axis = Axis3D::Rel::PrevX; break;
		//	case Axis3D::Rel::PrevY: axis = Axis3D::Rel::PrevY; break;
		//	case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::PrevZ; break;
		//	case Axis3D::Rel::NextX: axis = Axis3D::Rel::NextX; break;
		//	case Axis3D::Rel::NextY: axis = Axis3D::Rel::NextY; break;
		//	case Axis3D::Rel::NextZ: axis = Axis3D::Rel::NextZ; break;
			default: break;
		} break;
		case Axis3D::Diag::Prev: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::PrevZ;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::NextX: return Axis3D::Rel::NextY;
			case Axis3D::Rel::NextY: return Axis3D::Rel::NextZ;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::NextX;
			default: break;
		} break;
		case Axis3D::Diag::Next: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::PrevZ;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::NextX: return Axis3D::Rel::NextZ;
			case Axis3D::Rel::NextY: return Axis3D::Rel::NextX;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::NextY;
			default: break;
		} break;
		case Axis3D::Diag::DiagX: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::NextX; // PrevX(001)  ~  NextX(110)
			case Axis3D::Rel::PrevY: return Axis3D::Rel::NextZ; // PrevY(010) <<~ NextZ(011)
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::NextY; // PrevZ(100) ~>> NextY(101)
			case Axis3D::Rel::NextX: return Axis3D::Rel::PrevX; // NextX(110)  ~  PrevX(001)
			case Axis3D::Rel::NextY: return Axis3D::Rel::PrevZ; // NextY(101) <<~ PrevZ(100)
			case Axis3D::Rel::NextZ: return Axis3D::Rel::PrevY; // NextZ(011) ~>> PrevY(010)
			default: break;
		} break;
		case Axis3D::Diag::DiagY: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::NextZ;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::NextY;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::NextX;
			case Axis3D::Rel::NextX: return Axis3D::Rel::PrevZ;
			case Axis3D::Rel::NextY: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::PrevX;
			default: break;
		} break;
		case Axis3D::Diag::DiagZ: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::NextY;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::NextX;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::NextZ;
			case Axis3D::Rel::NextX: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::NextY: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::PrevZ;
			default: break;
		} break;
	}
	return axis;
}
static Axis3D::Rel s_absolute(const Axis3D::Flip & flip, const Axis3D::Rel & axis)
{
	switch (flip)
	{
		case Axis3D::Flip::None: switch (axis)
		{
		//	case Axis3D::Rel::PrevX: return Axis3D::Rel::PrevX;
		//	case Axis3D::Rel::PrevY: return Axis3D::Rel::PrevY;
		//	case Axis3D::Rel::PrevZ: return Axis3D::Rel::PrevZ;
		//	case Axis3D::Rel::NextX: return Axis3D::Rel::NextX;
		//	case Axis3D::Rel::NextY: return Axis3D::Rel::NextY;
		//	case Axis3D::Rel::NextZ: return Axis3D::Rel::NextZ;
			default: break;
		} break;
		case Axis3D::Flip::FlipX: switch (axis)
		{
		//	case Axis3D::Rel::PrevX: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::NextY;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::NextZ;
		//	case Axis3D::Rel::NextX: return Axis3D::Rel::NextX;
			case Axis3D::Rel::NextY: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::PrevZ;
			default: break;
		} break;
		case Axis3D::Flip::FlipY: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::NextX;
		//	case Axis3D::Rel::PrevY: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::NextZ;
			case Axis3D::Rel::NextX: return Axis3D::Rel::PrevX;
		//	case Axis3D::Rel::NextY: return Axis3D::Rel::NextY;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::PrevZ;
			default: break;
		} break;
		case Axis3D::Flip::FlipZ: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::NextX;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::NextY;
		//	case Axis3D::Rel::PrevZ: return Axis3D::Rel::PrevZ;
			case Axis3D::Rel::NextX: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::NextY: return Axis3D::Rel::PrevY;
		//	case Axis3D::Rel::NextZ: return Axis3D::Rel::NextZ;
			default: break;
		} break;
	}
	return axis;
}
Axis3D::Rel Axis3D::Orientation::absolute(const Axis3D::Rel & axis) const
{
	return s_absolute(GetFlip(), s_absolute(GetDiag(), axis));

	/*switch (GetDiag())
	{
		case Diag::Here: switch (axis)
		{
			//case Axis3D::Rel::PrevX: axis = Axis3D::Rel::PrevX; break;
			//case Axis3D::Rel::PrevY: axis = Axis3D::Rel::PrevY; break;
			//case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::PrevZ; break;
			//case Axis3D::Rel::NextX: axis = Axis3D::Rel::NextX; break;
			//case Axis3D::Rel::NextY: axis = Axis3D::Rel::NextY; break;
			//case Axis3D::Rel::NextZ: axis = Axis3D::Rel::NextZ; break;
			default: break;
		} break;
		case Diag::Prev: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::PrevZ; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::NextZ; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::NextX; break;
			default: break;
		} break;
		case Diag::Next: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::PrevZ; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::NextZ; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::NextY; break;
			default: break;
		} break;
		case Diag::DiagX: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::NextX; break; // PrevX(001)  ~  NextX(110)
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::NextZ; break; // PrevY(010) <<~ NextZ(011)
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::NextY; break; // PrevZ(100) ~>> NextY(101)
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::PrevX; break; // NextX(110)  ~  PrevX(001)
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::PrevZ; break; // NextY(101) <<~ PrevZ(100)
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::PrevY; break; // NextZ(011) ~>> PrevY(010)
			default: break;
		} break;
		case Diag::DiagY: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::NextZ; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::PrevZ; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::PrevX; break;
			default: break;
		} break;
		case Diag::DiagZ: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::NextZ; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::PrevZ; break;
			default: break;
		} break;
	}*/

	/*switch (GetFlip())
	{
		case Flip::None: switch (axis)
		{
			//case Axis3D::Rel::PrevX: axis = Axis3D::Rel::PrevX; break;
			//case Axis3D::Rel::PrevY: axis = Axis3D::Rel::PrevY; break;
			//case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::PrevZ; break;
			//case Axis3D::Rel::NextX: axis = Axis3D::Rel::NextX; break;
			//case Axis3D::Rel::NextY: axis = Axis3D::Rel::NextY; break;
			//case Axis3D::Rel::NextZ: axis = Axis3D::Rel::NextZ; break;
			default: break;
		} break;
		case Flip::FlipX: switch (axis)
		{
			//case Axis3D::Rel::PrevX: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::NextZ; break;
			//case Axis3D::Rel::NextX: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipY: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::NextX; break;
			//case Axis3D::Rel::PrevY: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::NextZ; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::PrevX; break;
			//case Axis3D::Rel::NextY: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipZ: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::NextY; break;
			//case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::PrevZ; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::PrevY; break;
			//case Axis3D::Rel::NextZ: axis = Axis3D::Rel::NextZ; break;
			default: break;
		} break;
	}*/

	//return axis;
}

static Axis3D::Rel s_relative(const Axis3D::Diag & diag, const Axis3D::Rel & axis)
{
	switch (diag)
	{
		case Axis3D::Diag::Here: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::PrevZ;
			case Axis3D::Rel::NextX: return Axis3D::Rel::NextX;
			case Axis3D::Rel::NextY: return Axis3D::Rel::NextY;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::NextZ;
			default: break;
		} break;
		case Axis3D::Diag::Prev: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::PrevZ;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::NextX: return Axis3D::Rel::NextZ;
			case Axis3D::Rel::NextY: return Axis3D::Rel::NextX;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::NextY;
			default: break;
		} break;
		case Axis3D::Diag::Next: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::PrevZ;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::NextX: return Axis3D::Rel::NextY;
			case Axis3D::Rel::NextY: return Axis3D::Rel::NextZ;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::NextX;
			default: break;
		} break;
		case Axis3D::Diag::DiagX: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::NextX;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::NextZ;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::NextY;
			case Axis3D::Rel::NextX: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::NextY: return Axis3D::Rel::PrevZ;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::PrevY;
			default: break;
		} break;
		case Axis3D::Diag::DiagY: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::NextZ;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::NextY;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::NextX;
			case Axis3D::Rel::NextX: return Axis3D::Rel::PrevZ;
			case Axis3D::Rel::NextY: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::PrevX;
			default: break;
		} break;
		case Axis3D::Diag::DiagZ: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::NextY;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::NextX;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::NextZ;
			case Axis3D::Rel::NextX: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::NextY: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::PrevZ;
			default: break;
		} break;
	}
	return axis;
}
static Axis3D::Rel s_relative(const Axis3D::Flip & flip, const Axis3D::Rel & axis)
{
	switch (flip)
	{
		case Axis3D::Flip::None: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::PrevZ;
			case Axis3D::Rel::NextX: return Axis3D::Rel::NextX;
			case Axis3D::Rel::NextY: return Axis3D::Rel::NextY;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::NextZ;
			default: break;
		} break;
		case Axis3D::Flip::FlipX: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::NextY;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::NextZ;
			case Axis3D::Rel::NextX: return Axis3D::Rel::NextX;
			case Axis3D::Rel::NextY: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::PrevZ;
			default: break;
		} break;
		case Axis3D::Flip::FlipY: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::NextX;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::NextZ;
			case Axis3D::Rel::NextX: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::NextY: return Axis3D::Rel::NextY;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::PrevZ;
			default: break;
		} break;
		case Axis3D::Flip::FlipZ: switch (axis)
		{
			case Axis3D::Rel::PrevX: return Axis3D::Rel::NextX;
			case Axis3D::Rel::PrevY: return Axis3D::Rel::NextY;
			case Axis3D::Rel::PrevZ: return Axis3D::Rel::PrevZ;
			case Axis3D::Rel::NextX: return Axis3D::Rel::PrevX;
			case Axis3D::Rel::NextY: return Axis3D::Rel::PrevY;
			case Axis3D::Rel::NextZ: return Axis3D::Rel::NextZ;
			default: break;
		} break;
	}
	return axis;
}
Axis3D::Rel Axis3D::Orientation::relative(const Axis3D::Rel & axis) const
{
	return s_relative(GetDiag(), s_relative(GetFlip(), axis));

	/*switch (GetFlip())
	{
		case Flip::None: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::PrevZ; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::NextZ; break;
			default: break;
		} break;
		case Flip::FlipX: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::NextZ; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipY: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::NextZ; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::PrevZ; break;
			default: break;
		} break;
		case Flip::FlipZ: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::PrevZ; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::NextZ; break;
			default: break;
		} break;
	}*/

	/*switch (GetDiag())
	{
		case Diag::Here: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::PrevZ; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::NextZ; break;
			default: break;
		} break;
		case Diag::Prev: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::PrevZ; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::NextZ; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::NextY; break;
			default: break;
		} break;
		case Diag::Next: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::PrevZ; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::NextZ; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::NextX; break;
			default: break;
		} break;
		case Diag::DiagX: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::NextZ; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::PrevZ; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::PrevY; break;
			default: break;
		} break;
		case Diag::DiagY: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::NextZ; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::PrevZ; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::PrevX; break;
			default: break;
		} break;
		case Diag::DiagZ: switch (axis)
		{
			case Axis3D::Rel::PrevX: axis = Axis3D::Rel::NextY; break;
			case Axis3D::Rel::PrevY: axis = Axis3D::Rel::NextX; break;
			case Axis3D::Rel::PrevZ: axis = Axis3D::Rel::NextZ; break;
			case Axis3D::Rel::NextX: axis = Axis3D::Rel::PrevY; break;
			case Axis3D::Rel::NextY: axis = Axis3D::Rel::PrevX; break;
			case Axis3D::Rel::NextZ: axis = Axis3D::Rel::PrevZ; break;
			default: break;
		} break;
	}*/

	//return axis;
}



static VectorU3 s_absolute(const Axis3D::Diag & diag, const VectorU3 & v)
{
	switch (diag)
	{
		case Axis3D::Diag::Here : return VectorU3(0 + v.X, 0 + v.Y, 0 + v.Z);
		case Axis3D::Diag::Prev : return VectorU3(0 + v.Z, 0 + v.X, 0 + v.Y);
		case Axis3D::Diag::Next : return VectorU3(0 + v.Y, 0 + v.Z, 0 + v.X);
		case Axis3D::Diag::DiagX: return VectorU3(1 - v.X, 1 - v.Z, 1 - v.Y);
		case Axis3D::Diag::DiagY: return VectorU3(1 - v.Z, 1 - v.Y, 1 - v.X);
		case Axis3D::Diag::DiagZ: return VectorU3(1 - v.Y, 1 - v.X, 1 - v.Z);
	}
	return v;
}
static VectorU3 s_absolute(const Axis3D::Flip & flip, const VectorU3 & v)
{
	switch (flip)
	{
		case Axis3D::Flip::None : return VectorU3(0 + v.X, 0 + v.Y, 0 + v.Z);
		case Axis3D::Flip::FlipX: return VectorU3(0 + v.X, 1 - v.Y, 1 - v.Z);
		case Axis3D::Flip::FlipY: return VectorU3(1 - v.X, 0 + v.Y, 1 - v.Z);
		case Axis3D::Flip::FlipZ: return VectorU3(1 - v.X, 1 - v.Y, 0 + v.Z);
	}
	return v;
}
VectorU3 Axis3D::Orientation::absolute(const VectorU3 & v) const
{
	return s_absolute(GetFlip(), s_absolute(GetDiag(), v));

	/*switch (GetDiag())
	{
		case Diag::Here : v = VectorU3(0 + v.X, 0 + v.Y, 0 + v.Z); break;
		case Diag::Prev : v = VectorU3(0 + v.Z, 0 + v.X, 0 + v.Y); break;
		case Diag::Next : v = VectorU3(0 + v.Y, 0 + v.Z, 0 + v.X); break;
		case Diag::DiagX: v = VectorU3(1 - v.X, 1 - v.Z, 1 - v.Y); break;
		case Diag::DiagY: v = VectorU3(1 - v.Z, 1 - v.Y, 1 - v.X); break;
		case Diag::DiagZ: v = VectorU3(1 - v.Y, 1 - v.X, 1 - v.Z); break;
	}*/

	/*switch (GetFlip())
	{
		case Flip::None : v = VectorU3(0 + v.X, 0 + v.Y, 0 + v.Z); break;
		case Flip::FlipX: v = VectorU3(0 + v.X, 1 - v.Y, 1 - v.Z); break;
		case Flip::FlipY: v = VectorU3(1 - v.X, 0 + v.Y, 1 - v.Z); break;
		case Flip::FlipZ: v = VectorU3(1 - v.X, 1 - v.Y, 0 + v.Z); break;
	}*/

	//return v;
}

static VectorF3 s_absolute(const Axis3D::Diag & diag, const VectorF3 & v)
{
	switch (diag)
	{
		case Axis3D::Diag::Here : return VectorF3(0.0f + v.X, 0.0f + v.Y, 0.0f + v.Z);
		case Axis3D::Diag::Prev : return VectorF3(0.0f + v.Z, 0.0f + v.X, 0.0f + v.Y);
		case Axis3D::Diag::Next : return VectorF3(0.0f + v.Y, 0.0f + v.Z, 0.0f + v.X);
		case Axis3D::Diag::DiagX: return VectorF3(1.0f - v.X, 1.0f - v.Z, 1.0f - v.Y);
		case Axis3D::Diag::DiagY: return VectorF3(1.0f - v.Z, 1.0f - v.Y, 1.0f - v.X);
		case Axis3D::Diag::DiagZ: return VectorF3(1.0f - v.Y, 1.0f - v.X, 1.0f - v.Z);
	}
	return v;
}
static VectorF3 s_absolute(const Axis3D::Flip & flip, const VectorF3 & v)
{
	switch (flip)
	{
		case Axis3D::Flip::None : return VectorF3(0.0f + v.X, 0.0f + v.Y, 0.0f + v.Z);
		case Axis3D::Flip::FlipX: return VectorF3(0.0f + v.X, 1.0f - v.Y, 1.0f - v.Z);
		case Axis3D::Flip::FlipY: return VectorF3(1.0f - v.X, 0.0f + v.Y, 1.0f - v.Z);
		case Axis3D::Flip::FlipZ: return VectorF3(1.0f - v.X, 1.0f - v.Y, 0.0f + v.Z);
	}
	return v;
}
VectorF3 Axis3D::Orientation::absolute(const VectorF3 & v) const
{
	return s_absolute(GetFlip(), s_absolute(GetDiag(), v));

	/*switch (GetDiag())
	{
		case Diag::Here : v = VectorF3(0.0f + v.X, 0.0f + v.Y, 0.0f + v.Z); break;
		case Diag::Prev : v = VectorF3(0.0f + v.Z, 0.0f + v.X, 0.0f + v.Y); break;
		case Diag::Next : v = VectorF3(0.0f + v.Y, 0.0f + v.Z, 0.0f + v.X); break;
		case Diag::DiagX: v = VectorF3(1.0f - v.X, 1.0f - v.Z, 1.0f - v.Y); break;
		case Diag::DiagY: v = VectorF3(1.0f - v.Z, 1.0f - v.Y, 1.0f - v.X); break;
		case Diag::DiagZ: v = VectorF3(1.0f - v.Y, 1.0f - v.X, 1.0f - v.Z); break;
	}*/

	/*switch (GetFlip())
	{
		case Flip::None : v = VectorF3(0.0f + v.X, 0.0f + v.Y, 0.0f + v.Z); break;
		case Flip::FlipX: v = VectorF3(0.0f + v.X, 1.0f - v.Y, 1.0f - v.Z); break;
		case Flip::FlipY: v = VectorF3(1.0f - v.X, 0.0f + v.Y, 1.0f - v.Z); break;
		case Flip::FlipZ: v = VectorF3(1.0f - v.X, 1.0f - v.Y, 0.0f + v.Z); break;
	}*/

	//return v;
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

static VectorU3 absolute_U3_SwizzleFunc_00(const VectorU3 & u) { return VectorU3(0 + u.X, 0 + u.Y, 0 + u.Z); }
static VectorU3 absolute_U3_SwizzleFunc_01(const VectorU3 & u) { return VectorU3(0 + u.Y, 0 + u.Z, 0 + u.X); }
static VectorU3 absolute_U3_SwizzleFunc_02(const VectorU3 & u) { return VectorU3(0 + u.Z, 0 + u.X, 0 + u.Y); }
static VectorU3 absolute_U3_SwizzleFunc_03(const VectorU3 & u) { return VectorU3(1 - u.X, 1 - u.Z, 1 - u.Y); }
static VectorU3 absolute_U3_SwizzleFunc_04(const VectorU3 & u) { return VectorU3(1 - u.Z, 1 - u.Y, 1 - u.X); }
static VectorU3 absolute_U3_SwizzleFunc_05(const VectorU3 & u) { return VectorU3(1 - u.Y, 1 - u.X, 1 - u.Z); }

static VectorU3 absolute_U3_SwizzleFunc_08(const VectorU3 & u) { return VectorU3(0 + u.X, 1 - u.Y, 1 - u.Z); }
static VectorU3 absolute_U3_SwizzleFunc_09(const VectorU3 & u) { return VectorU3(0 + u.Y, 1 - u.Z, 1 - u.X); }
static VectorU3 absolute_U3_SwizzleFunc_10(const VectorU3 & u) { return VectorU3(0 + u.Z, 1 - u.X, 1 - u.Y); }
static VectorU3 absolute_U3_SwizzleFunc_11(const VectorU3 & u) { return VectorU3(1 - u.X, 0 + u.Z, 0 + u.Y); }
static VectorU3 absolute_U3_SwizzleFunc_12(const VectorU3 & u) { return VectorU3(1 - u.Z, 0 + u.Y, 0 + u.X); }
static VectorU3 absolute_U3_SwizzleFunc_13(const VectorU3 & u) { return VectorU3(1 - u.Y, 0 + u.X, 0 + u.Z); }

static VectorU3 absolute_U3_SwizzleFunc_16(const VectorU3 & u) { return VectorU3(1 - u.X, 0 + u.Y, 1 - u.Z); }
static VectorU3 absolute_U3_SwizzleFunc_17(const VectorU3 & u) { return VectorU3(1 - u.Y, 0 + u.Z, 1 - u.X); }
static VectorU3 absolute_U3_SwizzleFunc_18(const VectorU3 & u) { return VectorU3(1 - u.Z, 0 + u.X, 1 - u.Y); }
static VectorU3 absolute_U3_SwizzleFunc_19(const VectorU3 & u) { return VectorU3(0 + u.X, 1 - u.Z, 0 + u.Y); }
static VectorU3 absolute_U3_SwizzleFunc_20(const VectorU3 & u) { return VectorU3(0 + u.Z, 1 - u.Y, 0 + u.X); }
static VectorU3 absolute_U3_SwizzleFunc_21(const VectorU3 & u) { return VectorU3(0 + u.Y, 1 - u.X, 0 + u.Z); }

static VectorU3 absolute_U3_SwizzleFunc_24(const VectorU3 & u) { return VectorU3(1 - u.X, 1 - u.Y, 0 + u.Z); }
static VectorU3 absolute_U3_SwizzleFunc_25(const VectorU3 & u) { return VectorU3(1 - u.Y, 1 - u.Z, 0 + u.X); }
static VectorU3 absolute_U3_SwizzleFunc_26(const VectorU3 & u) { return VectorU3(1 - u.Z, 1 - u.X, 0 + u.Y); }
static VectorU3 absolute_U3_SwizzleFunc_27(const VectorU3 & u) { return VectorU3(0 + u.X, 0 + u.Z, 1 - u.Y); }
static VectorU3 absolute_U3_SwizzleFunc_28(const VectorU3 & u) { return VectorU3(0 + u.Z, 0 + u.Y, 1 - u.X); }
static VectorU3 absolute_U3_SwizzleFunc_29(const VectorU3 & u) { return VectorU3(0 + u.Y, 0 + u.X, 1 - u.Z); }

Axis3D::Orientation::SwizzlerU_Ptr absolute_U3_SwizzleFunc_Array[32] = {
	&absolute_U3_SwizzleFunc_00,
	&absolute_U3_SwizzleFunc_01,
	&absolute_U3_SwizzleFunc_02,
	&absolute_U3_SwizzleFunc_03,
	&absolute_U3_SwizzleFunc_04,
	&absolute_U3_SwizzleFunc_05,
	nullptr,
	nullptr,
	&absolute_U3_SwizzleFunc_08,
	&absolute_U3_SwizzleFunc_09,
	&absolute_U3_SwizzleFunc_10,
	&absolute_U3_SwizzleFunc_11,
	&absolute_U3_SwizzleFunc_12,
	&absolute_U3_SwizzleFunc_13,
	nullptr,
	nullptr,
	&absolute_U3_SwizzleFunc_16,
	&absolute_U3_SwizzleFunc_17,
	&absolute_U3_SwizzleFunc_18,
	&absolute_U3_SwizzleFunc_19,
	&absolute_U3_SwizzleFunc_20,
	&absolute_U3_SwizzleFunc_21,
	nullptr,
	nullptr,
	&absolute_U3_SwizzleFunc_24,
	&absolute_U3_SwizzleFunc_25,
	&absolute_U3_SwizzleFunc_26,
	&absolute_U3_SwizzleFunc_27,
	&absolute_U3_SwizzleFunc_28,
	&absolute_U3_SwizzleFunc_29,
	nullptr,
	nullptr
};

Axis3D::Orientation::SwizzlerU_Ref Axis3D::Orientation::absolute_U_Func() const
{
	return *(absolute_U3_SwizzleFunc_Array[Value]);
}

static VectorF3 absolute_F3_SwizzleFunc_00(const VectorF3 & u) { return VectorF3(0.0f + u.X, 0.0f + u.Y, 0.0f + u.Z); }
static VectorF3 absolute_F3_SwizzleFunc_01(const VectorF3 & u) { return VectorF3(0.0f + u.Y, 0.0f + u.Z, 0.0f + u.X); }
static VectorF3 absolute_F3_SwizzleFunc_02(const VectorF3 & u) { return VectorF3(0.0f + u.Z, 0.0f + u.X, 0.0f + u.Y); }
static VectorF3 absolute_F3_SwizzleFunc_03(const VectorF3 & u) { return VectorF3(1.0f - u.X, 1.0f - u.Z, 1.0f - u.Y); }
static VectorF3 absolute_F3_SwizzleFunc_04(const VectorF3 & u) { return VectorF3(1.0f - u.Z, 1.0f - u.Y, 1.0f - u.X); }
static VectorF3 absolute_F3_SwizzleFunc_05(const VectorF3 & u) { return VectorF3(1.0f - u.Y, 1.0f - u.X, 1.0f - u.Z); }

static VectorF3 absolute_F3_SwizzleFunc_08(const VectorF3 & u) { return VectorF3(0.0f + u.X, 1.0f - u.Y, 1.0f - u.Z); }
static VectorF3 absolute_F3_SwizzleFunc_09(const VectorF3 & u) { return VectorF3(0.0f + u.Y, 1.0f - u.Z, 1.0f - u.X); }
static VectorF3 absolute_F3_SwizzleFunc_10(const VectorF3 & u) { return VectorF3(0.0f + u.Z, 1.0f - u.X, 1.0f - u.Y); }
static VectorF3 absolute_F3_SwizzleFunc_11(const VectorF3 & u) { return VectorF3(1.0f - u.X, 0.0f + u.Z, 0.0f + u.Y); }
static VectorF3 absolute_F3_SwizzleFunc_12(const VectorF3 & u) { return VectorF3(1.0f - u.Z, 0.0f + u.Y, 0.0f + u.X); }
static VectorF3 absolute_F3_SwizzleFunc_13(const VectorF3 & u) { return VectorF3(1.0f - u.Y, 0.0f + u.X, 0.0f + u.Z); }

static VectorF3 absolute_F3_SwizzleFunc_16(const VectorF3 & u) { return VectorF3(1.0f - u.X, 0.0f + u.Y, 1.0f - u.Z); }
static VectorF3 absolute_F3_SwizzleFunc_17(const VectorF3 & u) { return VectorF3(1.0f - u.Y, 0.0f + u.Z, 1.0f - u.X); }
static VectorF3 absolute_F3_SwizzleFunc_18(const VectorF3 & u) { return VectorF3(1.0f - u.Z, 0.0f + u.X, 1.0f - u.Y); }
static VectorF3 absolute_F3_SwizzleFunc_19(const VectorF3 & u) { return VectorF3(0.0f + u.X, 1.0f - u.Z, 0.0f + u.Y); }
static VectorF3 absolute_F3_SwizzleFunc_20(const VectorF3 & u) { return VectorF3(0.0f + u.Z, 1.0f - u.Y, 0.0f + u.X); }
static VectorF3 absolute_F3_SwizzleFunc_21(const VectorF3 & u) { return VectorF3(0.0f + u.Y, 1.0f - u.X, 0.0f + u.Z); }

static VectorF3 absolute_F3_SwizzleFunc_24(const VectorF3 & u) { return VectorF3(1.0f - u.X, 1.0f - u.Y, 0.0f + u.Z); }
static VectorF3 absolute_F3_SwizzleFunc_25(const VectorF3 & u) { return VectorF3(1.0f - u.Y, 1.0f - u.Z, 0.0f + u.X); }
static VectorF3 absolute_F3_SwizzleFunc_26(const VectorF3 & u) { return VectorF3(1.0f - u.Z, 1.0f - u.X, 0.0f + u.Y); }
static VectorF3 absolute_F3_SwizzleFunc_27(const VectorF3 & u) { return VectorF3(0.0f + u.X, 0.0f + u.Z, 1.0f - u.Y); }
static VectorF3 absolute_F3_SwizzleFunc_28(const VectorF3 & u) { return VectorF3(0.0f + u.Z, 0.0f + u.Y, 1.0f - u.X); }
static VectorF3 absolute_F3_SwizzleFunc_29(const VectorF3 & u) { return VectorF3(0.0f + u.Y, 0.0f + u.X, 1.0f - u.Z); }

Axis3D::Orientation::SwizzlerF_Ptr absolute_F3_SwizzleFunc_Array[32] = {
	&absolute_F3_SwizzleFunc_00,
	&absolute_F3_SwizzleFunc_01,
	&absolute_F3_SwizzleFunc_02,
	&absolute_F3_SwizzleFunc_03,
	&absolute_F3_SwizzleFunc_04,
	&absolute_F3_SwizzleFunc_05,
	nullptr,
	nullptr,
	&absolute_F3_SwizzleFunc_08,
	&absolute_F3_SwizzleFunc_09,
	&absolute_F3_SwizzleFunc_10,
	&absolute_F3_SwizzleFunc_11,
	&absolute_F3_SwizzleFunc_12,
	&absolute_F3_SwizzleFunc_13,
	nullptr,
	nullptr,
	&absolute_F3_SwizzleFunc_16,
	&absolute_F3_SwizzleFunc_17,
	&absolute_F3_SwizzleFunc_18,
	&absolute_F3_SwizzleFunc_19,
	&absolute_F3_SwizzleFunc_20,
	&absolute_F3_SwizzleFunc_21,
	nullptr,
	nullptr,
	&absolute_F3_SwizzleFunc_24,
	&absolute_F3_SwizzleFunc_25,
	&absolute_F3_SwizzleFunc_26,
	&absolute_F3_SwizzleFunc_27,
	&absolute_F3_SwizzleFunc_28,
	&absolute_F3_SwizzleFunc_29,
	nullptr,
	nullptr
};

Axis3D::Orientation::SwizzlerF_Ref Axis3D::Orientation::absolute_F_Func() const
{
	return *(absolute_F3_SwizzleFunc_Array[Value]);
}

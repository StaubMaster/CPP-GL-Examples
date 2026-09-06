#include "Funcs.hpp"
#include "Enums.hpp"

#include "ValueType/Vector/F3.hpp"



Axis3D::Abs Axis3D::RelToAbs(const Axis3D::Rel & axis)
{
	switch (axis)
	{
		case Rel::PrevX: return Abs::X;
		case Rel::NextX: return Abs::X;
		case Rel::PrevY: return Abs::Y;
		case Rel::NextY: return Abs::Y;
		case Rel::PrevZ: return Abs::Z;
		case Rel::NextZ: return Abs::Z;
		default: return Abs::None;
	}
}

VectorF3 Axis3D::ToVector(const Axis3D::Rel & axis)
{
	switch (axis)
	{
		case Rel::PrevX: return VectorF3(-1, 0, 0);
		case Rel::PrevY: return VectorF3(0, -1, 0);
		case Rel::PrevZ: return VectorF3(0, 0, -1);
		case Rel::NextX: return VectorF3(+1, 0, 0);
		case Rel::NextY: return VectorF3(0, +1, 0);
		case Rel::NextZ: return VectorF3(0, 0, +1);
		default: return VectorF3(0, 0, 0);
	}
}

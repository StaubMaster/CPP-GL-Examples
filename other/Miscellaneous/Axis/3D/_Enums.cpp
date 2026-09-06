#include "Show.hpp"
#include "Enums.hpp"

#include <sstream>

std::ostream & operator<<(std::ostream & s, Axis3D::Abs axis)
{
	switch (axis)
	{
		case AxisAbs::None : s << "None"; break;
		case AxisAbs::X: s << "X"; break;
		case AxisAbs::Y: s << "Y"; break;
		case AxisAbs::Z: s << "Z"; break;
		default : s << "AxisAbs:" << ((unsigned int)axis); break;
	}
	return s;
}

std::ostream & operator<<(std::ostream & s, Axis::Rel axis)
{
	switch (axis)
	{
		case Axis3D::Rel::None : s << "None"; break;
		case Axis3D::Rel::PrevX: s << "PrevX"; break;
		case Axis3D::Rel::PrevY: s << "PrevY"; break;
		case Axis3D::Rel::PrevZ: s << "PrevZ"; break;
		case Axis3D::Rel::NextX: s << "NextX"; break;
		case Axis3D::Rel::NextY: s << "NextY"; break;
		case Axis3D::Rel::NextZ: s << "NextZ"; break;
		case Axis3D::Rel::Here : s << "Here"; break;
		default : s << "Axis3D::Rel:" << ((unsigned int)axis); break;
	}
	return s;
}



AxisAbs Axis3D::RelToAxisAbs(Axis3D::Rel axis)
{
	switch (axis)
	{
		case Axis3D::Rel::PrevX: return AxisAbs::X;
		case Axis3D::Rel::NextX: return AxisAbs::X;
		case Axis3D::Rel::PrevY: return AxisAbs::Y;
		case Axis3D::Rel::NextY: return AxisAbs::Y;
		case Axis3D::Rel::PrevZ: return AxisAbs::Z;
		case Axis3D::Rel::NextZ: return AxisAbs::Z;
		default: return AxisAbs::None;
	}
}

VectorF3 AxisToVector(Axis3D::Rel axis)
{
	switch (axis)
	{
		case Axis3D::Rel::PrevX: return VectorF3(-1, 0, 0);
		case Axis3D::Rel::PrevY: return VectorF3(0, -1, 0);
		case Axis3D::Rel::PrevZ: return VectorF3(0, 0, -1);
		case Axis3D::Rel::NextX: return VectorF3(+1, 0, 0);
		case Axis3D::Rel::NextY: return VectorF3(0, +1, 0);
		case Axis3D::Rel::NextZ: return VectorF3(0, 0, +1);
		default: return VectorF3(0, 0, 0);
	}
}



std::ostream & operator<<(std::ostream & s, Diag diag)
{
	switch (diag)
	{
		case Diag::Here : s << "Here"; break;
		case Diag::Prev : s << "Prev"; break;
		case Diag::Next : s << "Next"; break;
		case Diag::DiagX: s << "DiagX"; break;
		case Diag::DiagY: s << "DiagY"; break;
		case Diag::DiagZ: s << "DiagZ"; break;
		default : s << "Diag:" << ((unsigned int)diag); break;
	}
	return s;
}



std::ostream & operator<<(std::ostream & s, Flip flip)
{
	switch (flip)
	{
		case Flip::None : s << "None"; break;
		case Flip::FlipX: s << "FlipX"; break;
		case Flip::FlipY: s << "FlipY"; break;
		case Flip::FlipZ: s << "FlipZ"; break;
		default : s << "Flip:" << ((unsigned int)flip); break;
	}
	return s;
}

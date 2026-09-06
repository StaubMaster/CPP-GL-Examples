#include "Show.hpp"
#include "Enums.hpp"

#include <sstream>



std::ostream & operator<<(std::ostream & s, const Axis3D::Abs & axis)
{
	switch (axis)
	{
		case Axis3D::Abs::None : s << "None"; break;
		case Axis3D::Abs::X: s << "X"; break;
		case Axis3D::Abs::Y: s << "Y"; break;
		case Axis3D::Abs::Z: s << "Z"; break;
		default : s << "Axis3D::Abs:" << ((unsigned int)axis); break;
	}
	return s;
}

std::ostream & operator<<(std::ostream & s, const Axis3D::Rel & axis)
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



std::ostream & operator<<(std::ostream & s, const Axis3D::Diag & diag)
{
	switch (diag)
	{
		case Axis3D::Diag::Here : s << "Here"; break;
		case Axis3D::Diag::Prev : s << "Prev"; break;
		case Axis3D::Diag::Next : s << "Next"; break;
		case Axis3D::Diag::DiagX: s << "DiagX"; break;
		case Axis3D::Diag::DiagY: s << "DiagY"; break;
		case Axis3D::Diag::DiagZ: s << "DiagZ"; break;
		default : s << "Axis3D::Diag:" << ((unsigned int)diag); break;
	}
	return s;
}

std::ostream & operator<<(std::ostream & s, const Axis3D::Flip & flip)
{
	switch (flip)
	{
		case Axis3D::Flip::None : s << "None"; break;
		case Axis3D::Flip::FlipX: s << "FlipX"; break;
		case Axis3D::Flip::FlipY: s << "FlipY"; break;
		case Axis3D::Flip::FlipZ: s << "FlipZ"; break;
		default : s << "Axis3D::Orientation::Flip:" << ((unsigned int)flip); break;
	}
	return s;
}

#include "Show.hpp"
#include "Enums.hpp"

#include <sstream>



std::ostream & operator<<(std::ostream & s, const Axis2D::Abs & axis)
{
	switch (axis)
	{
		case Axis2D::Abs::None : s << "None"; break;
		case Axis2D::Abs::X: s << "X"; break;
		case Axis2D::Abs::Y: s << "Y"; break;
		default : s << "Axis2D::Abs:" << ((unsigned int)axis); break;
	}
	return s;
}

std::ostream & operator<<(std::ostream & s, const Axis2D::Rel & axis)
{
	switch (axis)
	{
		case Axis2D::Rel::None : s << "None"; break;
		case Axis2D::Rel::PrevX: s << "PrevX"; break;
		case Axis2D::Rel::PrevY: s << "PrevY"; break;
	//	case Axis2D::Rel::PrevZ: s << "PrevZ"; break;
		case Axis2D::Rel::NextX: s << "NextX"; break;
		case Axis2D::Rel::NextY: s << "NextY"; break;
	//	case Axis2D::Rel::NextZ: s << "NextZ"; break;
		case Axis2D::Rel::Here : s << "Here"; break;
		default : s << "Axis2D::Rel:" << ((unsigned int)axis); break;
	}
	return s;
}



std::ostream & operator<<(std::ostream & s, const Axis2D::Diag & diag)
{
	switch (diag)
	{
		case Axis2D::Diag::Normal0: s << "Normal0"; break;
		case Axis2D::Diag::Invert0: s << "Invert0"; break;
		case Axis2D::Diag::Normal1: s << "Normal1"; break;
		case Axis2D::Diag::Invert1: s << "Invert1"; break;
		default : s << "Axis2D::Diag:" << ((unsigned int)diag); break;
	}
	return s;
}

std::ostream & operator<<(std::ostream & s, const Axis2D::Flip & flip)
{
	switch (flip)
	{
		case Axis2D::Flip::None : s << "None"; break;
		case Axis2D::Flip::FlipX: s << "FlipX"; break;
		case Axis2D::Flip::FlipY: s << "FlipY"; break;
		default : s << "Axis2D::Orientation::Flip:" << ((unsigned int)flip); break;
	}
	return s;
}

#include "VoxelEnums.hpp"
#include <sstream>



std::ostream & operator<<(std::ostream & s, AxisAbs axis)
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

std::ostream & operator<<(std::ostream & s, AxisRel axis)
{
	switch (axis)
	{
		case AxisRel::None : s << "None"; break;
		case AxisRel::PrevX: s << "PrevX"; break;
		case AxisRel::PrevY: s << "PrevY"; break;
		case AxisRel::PrevZ: s << "PrevZ"; break;
		case AxisRel::NextX: s << "NextX"; break;
		case AxisRel::NextY: s << "NextY"; break;
		case AxisRel::NextZ: s << "NextZ"; break;
		case AxisRel::Here : s << "Here"; break;
		default : s << "AxisRel:" << ((unsigned int)axis); break;
	}
	return s;
}



AxisAbs AxisRelToAxisAbs(AxisRel axis)
{
	switch (axis)
	{
		case AxisRel::PrevX: return AxisAbs::X;
		case AxisRel::NextX: return AxisAbs::X;
		case AxisRel::PrevY: return AxisAbs::Y;
		case AxisRel::NextY: return AxisAbs::Y;
		case AxisRel::PrevZ: return AxisAbs::Z;
		case AxisRel::NextZ: return AxisAbs::Z;
		default: return AxisAbs::None;
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

#include "VoxelEnums.hpp"
#include <sstream>



std::ostream & operator<<(std::ostream & s, Axis axis)
{
	switch (axis)
	{
		case Axis::Here : s << "Here"; break;
		case Axis::PrevX: s << "PrevX"; break;
		case Axis::PrevY: s << "PrevY"; break;
		case Axis::PrevZ: s << "PrevZ"; break;
		case Axis::NextX: s << "NextX"; break;
		case Axis::NextY: s << "NextY"; break;
		case Axis::NextZ: s << "NextZ"; break;
		case Axis::None : s << "None"; break;
		default : s << "Axis:" << ((unsigned int)axis); break;
	}
	return s;
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

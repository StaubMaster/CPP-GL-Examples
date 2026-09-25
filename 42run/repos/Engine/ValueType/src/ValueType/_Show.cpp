#include "ValueType/_Show.hpp"
#include "ValueType/_Include.hpp"

#include <iostream>


static const char * ToString(bool val) { if (val) { return "true"; } else { return "false"; } }

/*
"( "	" )"
"{ "	" }"
"[ "	" ]"
" | "	" : "
*/

std::ostream & operator<<(std::ostream & os, const Bool2 & obj) { return os << "( " << ToString(obj.GetX()) << " : " << ToString(obj.GetY()) << " )"; }
std::ostream & operator<<(std::ostream & os, const Bool3 & obj) { return os << "( " << ToString(obj.GetX()) << " : " << ToString(obj.GetY()) << " : " << ToString(obj.GetZ()) << " )"; }
std::ostream & operator<<(std::ostream & os, const Bool4 & obj) { return os << "( " << ToString(obj.GetX()) << " : " << ToString(obj.GetY()) << " : " << ToString(obj.GetZ()) << " : " << ToString(obj.GetW()) << " )"; }

std::ostream & operator<<(std::ostream & os, const VectorF2 & obj) { return os << "( " << obj.X << " | " << obj.Y << " )"; }
std::ostream & operator<<(std::ostream & os, const VectorF3 & obj) { return os << "( " << obj.X << " | " << obj.Y << " | " << obj.Z << " )"; }
std::ostream & operator<<(std::ostream & os, const VectorF4 & obj) { return os << "( " << obj.X << " | " << obj.Y << " | " << obj.Z << " | " << obj.W << " )"; }
std::ostream & operator<<(std::ostream & os, const VectorU2 & obj) { return os << "[ " << obj.X << " | " << obj.Y << " ]"; }
std::ostream & operator<<(std::ostream & os, const VectorU3 & obj) { return os << "[ " << obj.X << " | " << obj.Y << " | " << obj.Z << " ]"; }
std::ostream & operator<<(std::ostream & os, const VectorI2 & obj) { return os << "[ " << obj.X << " | " << obj.Y << " ]"; }
std::ostream & operator<<(std::ostream & os, const VectorI3 & obj) { return os << "[ " << obj.X << " | " << obj.Y << " | " << obj.Z << " ]"; }

std::ostream & operator<<(std::ostream & os, const BoxF1 & obj) { return os << "{ " << obj.Min << " : " << obj.Max << " }"; }
std::ostream & operator<<(std::ostream & os, const BoxF2 & obj) { return os << "{ " << obj.Min << " : " << obj.Max << " }"; }
std::ostream & operator<<(std::ostream & os, const BoxF3 & obj) { return os << "{ " << obj.Min << " : " << obj.Max << " }"; }
std::ostream & operator<<(std::ostream & os, const BoxU2 & obj) { return os << "{ " << obj.Min << " : " << obj.Max << " }"; }
std::ostream & operator<<(std::ostream & os, const BoxU3 & obj) { return os << "{ " << obj.Min << " : " << obj.Max << " }"; }
std::ostream & operator<<(std::ostream & os, const BoxI2 & obj) { return os << "{ " << obj.Min << " : " << obj.Max << " }"; }
std::ostream & operator<<(std::ostream & os, const BoxI3 & obj) { return os << "{ " << obj.Min << " : " << obj.Max << " }"; }

//std::ostream & operator<<(std::ostream & os, const LineF2 & obj) { return os; }
//std::ostream & operator<<(std::ostream & os, const LineF3 & obj) { return os; }

//std::ostream & operator<<(std::ostream & os, const RayF2 & obj) { return os; }
//std::ostream & operator<<(std::ostream & os, const RayF3 & obj) { return os; }

std::ostream & operator<<(std::ostream & os, const Angle & obj)
{
	//os << obj.ToDegrees() << "°"; // Degree symbol dosnt work on all Terminals (Windows at Home)
	os << obj.ToDegrees() << "deg";
	//os << obj.ToRadians() << "rad";
	return os;
}
std::ostream & operator<<(std::ostream & os, const EulerAngle3D & obj)
{
	os << "( Z: " << obj.Z0 << " | X: " << obj.X1 << " | Y: " << obj.Y2 << " )";
	return os;
}

std::ostream & operator<<(std::ostream & os, const Trans2D & obj)
{
	os << "{ " << obj.Pos << " | " << obj.Rot << " }";
	return os;
}
std::ostream & operator<<(std::ostream & os, const Trans3D & obj)
{
	os << "{ " << obj.Position << " | " << obj.Rotation << " }";
	return os;
}



std::ostream & operator<<(std::ostream & os, const ColorF4 & obj)
{
	os << "(" << " R:" << obj.R << " G:" << obj.G << " B:" << obj.B << " A:" << obj.A << " )";
	return os;
}
std::ostream & operator<<(std::ostream & os, const ColorU4 & obj)
{
	os << "(" << " R:" << (unsigned int)obj.R << " G:" << (unsigned int)obj.G << " B:" << (unsigned int)obj.B << " A:" << (unsigned int)obj.A << " )";
	// maybe do Hex ?
	return os;
}



std::ostream & operator<<(std::ostream & os, const NormalPlaneF3 & obj)
{
	os << "{ " << obj.Origin << " | " << obj.Normal << " }";
	return os;
}
std::ostream & operator<<(std::ostream & os, const TriangleF3 & obj)
{
	os << "{ " << obj.A << " | " << obj.B << " | " << obj.C << " }";
	return os;
}
std::ostream & operator<<(std::ostream & os, const Undex & obj)
{
	if (obj.IsValid())
	{
		os << "[" << obj.Value << "]";
	}
	else
	{
		os << "[!]";
	}
	return os;
}

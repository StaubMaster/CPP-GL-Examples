#include "ValueType/Ray/F2.hpp"
#include "ValueType/Line/F2.hpp"

//#include <math.h>



RayF2::RayF2(const VectorF2 & pos, const VectorF2 & dir)
	: Pos(pos)
	, Dir(dir)
{ }
RayF2::RayF2(const LineF2 & line)
	: Pos(line.Origin)
	, Dir(line.Differance())
{ }



VectorF2 RayF2::ToPoint(float scalar) const
{
	return Pos + (Dir * scalar);
}
LineF2 RayF2::ToLine(float scalar) const
{
	return LineF2(Pos, Pos + (Dir * scalar));
}
LineF2 RayF2::ToLine(float scalar0, float scalar1) const
{
	return LineF2(Pos + (Dir * scalar0), Pos + (Dir * scalar1));
}

VectorF2 RayF2::Normal() const
{
	return Dir.cross(1.0f).normalize();
}


//RayF2::Interval::Interval(const RayF2 & ray, float inter = NAN, int index = -1) :
//	Ray(ray), Inter(inter), Index(index) { }

/*RayF2::Interval RayF2::Ray_Point(VectorF2 p)
{
	float dot = VectorF2::dot(Dir, Pos - p);
	float sqr = Dir.length2();
	return RayF2::Interval(*this, -(dot / sqr));
}*/

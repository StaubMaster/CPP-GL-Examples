#include "ValueType/Light/Spot.hpp"



LightSpot::LightSpot(float intensity, ColorF4 color, VectorF3 pos, VectorF3 dir, RangeF range)
	: Base(intensity, color)
	, Pos(pos)
	, Dir(dir)
	, Range(range)
{ }
LightSpot::LightSpot(LightBase base, VectorF3 pos, VectorF3 dir, RangeF range)
	: Base(base)
	, Pos(pos)
	, Dir(dir)
	, Range(range)
{ }



#include "ValueType/Ray/F3.hpp"
#include "ValueType/Line/F3.hpp"

LightSpot::LightSpot(LightBase base, RayF3 ray, RangeF range)
	: Base(base)
	, Pos(ray.Pos)
	, Dir(ray.Dir)
	, Range(range)
{ }
LightSpot::LightSpot(LightBase base, LineF3 line, RangeF range)
	: Base(base)
	, Pos(line.Origin)
	, Dir(line.Differance().normalize())
	, Range(range)
{ }

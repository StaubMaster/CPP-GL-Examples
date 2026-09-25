#include "ValueType/Light/Point.hpp"



LightPoint::LightPoint(float intensity, ColorF4 color, VectorF3 pos)
	: Base(intensity, color)
	, Pos(pos)
{ }
LightPoint::LightPoint(LightBase base, VectorF3 pos)
	: Base(base)
	, Pos(pos)
{ }

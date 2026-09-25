#include "ValueType/Light/Direction.hpp"



LightDirection::LightDirection(float intensity, ColorF4 color, VectorF3 dir)
	: Base(intensity, color)
	, Dir(dir)
{ }
LightDirection::LightDirection(LightBase base, VectorF3 dir)
	: Base(base)
	, Dir(dir)
{ }

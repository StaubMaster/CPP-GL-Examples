#ifndef  LIGHT_POINT_HPP
# define LIGHT_POINT_HPP

# include "ValueType/Light/Base.hpp"
# include "ValueType/Vector/F3.hpp"

struct LightPoint
{
	public:
	LightBase	Base;
	VectorF3	Pos;

	public:
	~LightPoint() = default;
	LightPoint() = default;
	LightPoint(const LightPoint & other) = default;
	LightPoint & operator=(const LightPoint & other) = default;

	public:
	LightPoint(float intensity, ColorF4 color, VectorF3 pos);
	LightPoint(LightBase base, VectorF3 pos);
};

#endif
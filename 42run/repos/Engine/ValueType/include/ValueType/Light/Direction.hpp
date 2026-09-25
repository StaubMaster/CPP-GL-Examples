#ifndef  LIGHT_DIRECTION_HPP
# define LIGHT_DIRECTION_HPP

# include "ValueType/Light/Base.hpp"
# include "ValueType/Vector/F3.hpp"

struct LightDirection
{
	public:
	LightBase	Base;
	VectorF3	Dir;

	public:
	~LightDirection() = default;
	LightDirection() = default;
	LightDirection(const LightDirection & other) = default;
	LightDirection & operator=(const LightDirection & other) = default;

	public:
	LightDirection(float intensity, ColorF4 color, VectorF3 dir);
	LightDirection(LightBase base, VectorF3 dir);
};

#endif
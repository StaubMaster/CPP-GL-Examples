#ifndef  LIGHT_BASE_HPP
# define LIGHT_BASE_HPP

# include "ValueType/Color/F4.hpp"

struct LightBase
{
	public:
	float	Intensity;
	ColorF4	Color;

	public:
	~LightBase() = default;
	LightBase() = default;
	LightBase(const LightBase & other) = default;
	LightBase & operator=(const LightBase & other) = default;

	public:
	LightBase(float intensity, ColorF4 color);
};

#endif
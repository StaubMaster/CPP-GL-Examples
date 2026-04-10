#ifndef  PLANE_HPP
# define PLANE_HPP

# define PLANE_SCALE 0.0625
# define PLANE_VALUES_PER_SIDE 16
# define PLANE_VALUES_PER_AREA PLANE_VALUES_PER_SIDE * PLANE_VALUES_PER_SIDE

# include "ValueType/Undex2D.hpp"

struct Perlin2D;

struct Plane
{
	float		Values[PLANE_VALUES_PER_AREA];
	Undex2D		Undex;

	float &			operator[](Undex2D udx);
	const float &	operator[](Undex2D udx) const;

	~Plane();
	Plane();
	Plane(const Plane & other) = delete;
	Plane & operator=(const Plane & other) = delete;

	void Generate(const Perlin2D & noise);
};

#endif

#ifndef  PERLIN_3D_HPP
# define PERLIN_3D_HPP

# include "ValueType/VectorU3.hpp"
# include "ValueType/VectorF3.hpp"

struct Perlin3D
{
	VectorU3	Count;
	VectorF3 *	Data;

	~Perlin3D();
	Perlin3D();
	Perlin3D(const Perlin3D & other);
	Perlin3D & operator=(const Perlin3D & other);
	
	Perlin3D(VectorU3 count);

	static Perlin3D		Random(VectorU3 count);

	VectorU3		Normalize(VectorF3 node) const;

	float	Calculate(VectorF3 pos) const;
};

#endif
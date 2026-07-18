#ifndef  PERLIN_3D_HPP
# define PERLIN_3D_HPP

# include "ValueType/Vector/U3.hpp"
# include "ValueType/Vector/F3.hpp"
# include "Generics/Container/Array3D.hpp"

struct Perlin3D
{
	Array3D<VectorF3>	Nodes;

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
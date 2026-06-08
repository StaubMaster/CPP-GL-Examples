#ifndef  PERLIN_2D_HPP
# define PERLIN_2D_HPP

# include "ValueType/Vector/U2.hpp"
# include "ValueType/Vector/F2.hpp"
# include "Miscellaneous/Container/Array2D.hpp"

struct Perlin2D
{
	Array2D<VectorF2>	Nodes;

	~Perlin2D();
	Perlin2D();
	Perlin2D(const Perlin2D & other);
	Perlin2D & operator=(const Perlin2D & other);
	
	Perlin2D(VectorU2 count);

	static Perlin2D		Random(VectorU2 count);

	VectorU2		Normalize(VectorF2 node) const;

	float	Calculate(VectorF2 pos) const;
};

#endif
#ifndef  PERLIN_2D_HPP
# define PERLIN_2D_HPP

# include "ValueType/Vector/F2.hpp"
# include "ValueType/Vector/U2.hpp"
# include "Generics/Container/Array2D.hpp"

struct Perlin2D
{
	Array2D<VectorF2>	Nodes;

	VectorU2	Clamp(const VectorF2 & pos) const;

	~Perlin2D() = default;
	Perlin2D() = default;
	Perlin2D(const Perlin2D & other) = default;
	Perlin2D & operator=(const Perlin2D & other) = default;

	Perlin2D(const VectorU2 & size);

	static Perlin2D		Random(const VectorU2 & size);

	float	Generate(const VectorF2 & pos) const;
};

#endif
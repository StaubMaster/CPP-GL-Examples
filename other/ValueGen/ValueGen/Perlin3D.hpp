#ifndef  PERLIN_3D_HPP
# define PERLIN_3D_HPP

# include "ValueType/Vector/U3.hpp"
# include "ValueType/Vector/F3.hpp"
# include "Generics/Container/Array3D.hpp"

struct Perlin3D
{
	Array3D<VectorF3>	Nodes;

	VectorU3	Clamp(const VectorF3 & pos) const;

	~Perlin3D() = default;
	Perlin3D() = default;
	Perlin3D(const Perlin3D & other) = default;
	Perlin3D & operator=(const Perlin3D & other) = default;

	Perlin3D(const VectorU3 & size);

	static Perlin3D		Random(const VectorU3 & size);

	float	Generate(const VectorF3 & pos) const;
};

#endif
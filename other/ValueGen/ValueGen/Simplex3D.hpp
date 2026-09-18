#ifndef  SIMPLEX_3D_HPP
# define SIMPLEX_3D_HPP

# include "ValueType/Vector/F3.hpp"

//# include "ValueType/Vector/U3.hpp"
//# include "Generics/Container/Array2D.hpp"

struct Simplex3D
{
	static void init();

	float	Generate(const VectorF3 & pos) const;
};

#endif
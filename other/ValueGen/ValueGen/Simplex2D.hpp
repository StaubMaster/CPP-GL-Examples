#ifndef  SIMPLEX_2D_HPP
# define SIMPLEX_2D_HPP

# include "ValueType/Vector/F2.hpp"

//# include "ValueType/Vector/U2.hpp"
//# include "Generics/Container/Array2D.hpp"

struct Simplex2D
{
	static void init();

	float	Generate(const VectorF2 & pos) const;
};

#endif
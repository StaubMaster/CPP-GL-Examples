#ifndef  UNIFORM_MATRIX_2_2_HPP
# define UNIFORM_MATRIX_2_2_HPP

# include "Graphics/Uniform/General/FloatNType.hpp"

struct Matrix2x2;

namespace Uniform
{
typedef FloatNType<2, 2, 1, ::Matrix2x2> Matrix2x2;
};

#endif
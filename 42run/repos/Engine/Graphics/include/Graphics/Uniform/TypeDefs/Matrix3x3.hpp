#ifndef  UNIFORM_MATRIX_3_3_HPP
# define UNIFORM_MATRIX_3_3_HPP

# include "Graphics/Uniform/General/FloatNType.hpp"

struct Matrix3x3;

namespace Uniform
{
typedef FloatNType<3, 3, 1, ::Matrix3x3> Matrix3x3;
};

#endif
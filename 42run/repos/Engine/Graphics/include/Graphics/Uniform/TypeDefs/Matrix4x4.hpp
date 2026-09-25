#ifndef  UNIFORM_MATRIX_4_4_HPP
# define UNIFORM_MATRIX_4_4_HPP

# include "Graphics/Uniform/General/FloatNType.hpp"

struct Matrix4x4;

namespace Uniform
{
typedef FloatNType<4, 4, 1, ::Matrix4x4> Matrix4x4;
};

#endif
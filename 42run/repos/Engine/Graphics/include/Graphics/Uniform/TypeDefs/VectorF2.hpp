#ifndef  UNIFORM_POINT_2D_HPP
# define UNIFORM_POINT_2D_HPP

# include "Graphics/Uniform/General/FloatNType.hpp"

struct VectorF2;

namespace Uniform
{
typedef FloatNType<2, 1, 1, ::VectorF2> VectorF2;

template <unsigned int Count>
using VectorF2Array = FloatNType<2, 1, Count, ::VectorF2>;
};

#endif
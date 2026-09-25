#ifndef  UNIFORM_POINT_3D_HPP
# define UNIFORM_POINT_3D_HPP

# include "Graphics/Uniform/General/FloatNType.hpp"

struct VectorF3;

namespace Uniform
{
typedef FloatNType<3, 1, 1, ::VectorF3> VectorF3;
};

#endif
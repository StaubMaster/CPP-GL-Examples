#ifndef  UNIFORM_ANGLE_HPP
# define UNIFORM_ANGLE_HPP

# include "Graphics/Uniform/General/FloatNType.hpp"

struct Angle;

namespace Uniform
{
typedef FloatNType<1, 1, 1, ::Angle> Angle;
};

#endif
#ifndef  UNIFORM_DEPTH_FACTORS_HPP
# define UNIFORM_DEPTH_FACTORS_HPP

# include "Graphics/Uniform/General/FloatNType.hpp"

struct DepthFactors;

namespace Uniform
{
typedef FloatNType<1, 1, 7, ::DepthFactors> DepthFactors;
};

#endif
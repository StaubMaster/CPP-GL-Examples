#ifndef  UNIFORM_COLOR_F4_HPP
# define UNIFORM_COLOR_F4_HPP

# include "Graphics/Uniform/General/FloatNType.hpp"

struct ColorF4;

namespace Uniform
{
typedef FloatNType<4, 1, 1, ::ColorF4> ColorF4;

template <unsigned int Count>
using ColorF4Array = FloatNType<4, 1, Count, ::ColorF4>;
};

#endif
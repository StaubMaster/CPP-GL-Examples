#ifndef  PADDED_BLOCK_LIGHT_BASE_HPP
# define PADDED_BLOCK_LIGHT_BASE_HPP

# include "Graphics/PaddedBlock/TypeDefs/Float.hpp"
# include "Graphics/PaddedBlock/TypeDefs/ColorF4.hpp"
# include "ValueType/Light/Base.hpp"

namespace PaddedBlock
{
struct LightBase
{
	PaddedBlock::Float		Intensity;
	PaddedBlock::ColorF4	Color;
	LightBase & operator=(const ::LightBase & object);
};
};

#endif
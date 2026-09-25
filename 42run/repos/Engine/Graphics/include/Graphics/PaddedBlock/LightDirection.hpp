#ifndef  PADDED_BLOCK_LIGHT_DIRECTION_HPP
# define PADDED_BLOCK_LIGHT_DIRECTION_HPP

# include "Graphics/PaddedBlock/LightBase.hpp"
# include "Graphics/PaddedBlock/TypeDefs/VectorF3.hpp"
# include "ValueType/Light/Direction.hpp"

namespace PaddedBlock
{
struct LightDirection
{
	PaddedBlock::LightBase	Base;
	PaddedBlock::VectorF3	Dir;
	LightDirection & operator=(const ::LightDirection & object);
};
};

#endif
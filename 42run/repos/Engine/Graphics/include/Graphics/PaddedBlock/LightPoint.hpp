#ifndef  PADDED_BLOCK_LIGHT_POINT_HPP
# define PADDED_BLOCK_LIGHT_POINT_HPP

# include "Graphics/PaddedBlock/LightBase.hpp"
# include "Graphics/PaddedBlock/TypeDefs/VectorF3.hpp"
# include "ValueType/Light/Point.hpp"

namespace PaddedBlock
{
struct LightPoint
{
	PaddedBlock::LightBase	Base;
	PaddedBlock::VectorF3	Pos;
	LightPoint & operator=(const ::LightPoint & object);
};
};

#endif
#ifndef  PADDED_BLOCK_LIGHT_SPOT_HPP
# define PADDED_BLOCK_LIGHT_SPOT_HPP

# include "Graphics/PaddedBlock/LightBase.hpp"
# include "Graphics/PaddedBlock/TypeDefs/VectorF3.hpp"
# include "Graphics/PaddedBlock/TypeDefs/RangeF.hpp"
# include "ValueType/Light/Spot.hpp"

namespace PaddedBlock
{
struct LightSpot
{
	PaddedBlock::LightBase	Base;
	PaddedBlock::VectorF3	Pos;
	PaddedBlock::VectorF3	Dir;
	PaddedBlock::RangeF		Range;
	LightSpot & operator=(const ::LightSpot & object);
};
};

#endif
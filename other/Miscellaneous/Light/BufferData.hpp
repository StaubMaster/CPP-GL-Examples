#ifndef  LIGHT_BUFFER_DATA_HPP
# define LIGHT_BUFFER_DATA_HPP

# include "Graphics/PaddedBlock/LightBase.hpp"
# include "Graphics/PaddedBlock/LightDirection.hpp"
# include "Graphics/PaddedBlock/LightPoint.hpp"
# include "Graphics/PaddedBlock/LightSpot.hpp"
# include "Graphics/PaddedBlock/TypeDefs/UInt.hpp"

struct LightBufferData
{
	PaddedBlock::LightBase			Ambient;
	PaddedBlock::LightDirection		Solar;
	PaddedBlock::UInt				PointCount;
	PaddedBlock::LightPoint			Point[1];
	PaddedBlock::UInt				SpotCount;
	PaddedBlock::LightSpot			Spot[4];
};

#endif
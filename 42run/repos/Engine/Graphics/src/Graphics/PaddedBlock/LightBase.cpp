#include "Graphics/PaddedBlock/LightBase.hpp"



PaddedBlock::LightBase & PaddedBlock::LightBase::operator=(const ::LightBase & object)
{
	Intensity = object.Intensity;
	Color = object.Color;
	return *this;
}

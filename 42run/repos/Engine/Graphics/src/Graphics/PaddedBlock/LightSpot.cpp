#include "Graphics/PaddedBlock/LightSpot.hpp"



PaddedBlock::LightSpot & PaddedBlock::LightSpot::operator=(const ::LightSpot & object)
{
	Base = object.Base;
	Pos = object.Pos;
	Dir = object.Dir;
	Range = object.Range;
	return *this;
}

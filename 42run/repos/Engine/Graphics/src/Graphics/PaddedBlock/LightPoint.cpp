#include "Graphics/PaddedBlock/LightPoint.hpp"



PaddedBlock::LightPoint & PaddedBlock::LightPoint::operator=(const ::LightPoint & object)
{
	Base = object.Base;
	Pos = object.Pos;
	return *this;
}

#include "Graphics/PaddedBlock/LightDirection.hpp"



PaddedBlock::LightDirection & PaddedBlock::LightDirection::operator=(const ::LightDirection & object)
{
	Base = object.Base;
	Dir = object.Dir;
	return *this;
}

#include "LightShaderLayout.hpp"

#include "ValueType/Light/Base.hpp"
#include "ValueType/Light/Direction.hpp"
#include "ValueType/Light/Point.hpp"
#include "ValueType/Light/Spot.hpp"



PaddedBlock::LightBase & PaddedBlock::LightBase::operator=(const ::LightBase & object)
{
	Intensity = object.Intensity;
	Color = object.Color;
	return *this;
}
PaddedBlock::LightDirection & PaddedBlock::LightDirection::operator=(const ::LightDirection & object)
{
	Base = object.Base;
	Dir = object.Dir;
	return *this;
}
PaddedBlock::LightPoint & PaddedBlock::LightPoint::operator=(const ::LightPoint & object)
{
	Base = object.Base;
	Pos = object.Pos;
	return *this;
}
PaddedBlock::LightSpot & PaddedBlock::LightSpot::operator=(const ::LightSpot & object)
{
	Base = object.Base;
	Pos = object.Pos;
	Dir = object.Dir;
	Range = object.Range;
	return *this;
}



void LightBufferData::Put(Buffer::Uniform & buffer)
{
	Container::Void void_data;
	void_data.Data = this;
	void_data.Size = sizeof(LightBufferData);

	buffer.DataFull(void_data);
	buffer.BindBase();
}



LightShaderLayout::~LightShaderLayout()
{ }
LightShaderLayout::LightShaderLayout()
	: PolyHedraFull::ShaderLayout()
	, LightUniform(*this, "Lights")
{ }

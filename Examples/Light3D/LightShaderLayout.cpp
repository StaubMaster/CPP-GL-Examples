#include "LightShaderLayout.hpp"

#include "ValueType/LightBase.hpp"
#include "ValueType/LightSolar.hpp"
#include "ValueType/LightSpot.hpp"



UniformBlock::Float & UniformBlock::Float::operator=(const float & object) { Value = object; return *this; }
UniformBlock::UInt & UniformBlock::UInt::operator=(const unsigned int & object) { Value = object; return *this; }
UniformBlock::VectorF3 & UniformBlock::VectorF3::operator=(const ::VectorF3 & object) { Value = object; return *this; }
UniformBlock::ColorF4 & UniformBlock::ColorF4::operator=(const ::ColorF4 & object) { Value = object; return *this; }
UniformBlock::Range & UniformBlock::Range::operator=(const ::Range & object) { Value = object; return *this; }
UniformBlock::LightBase & UniformBlock::LightBase::operator=(const ::LightBase & object)
{
	Intensity = object.Intensity;
	Color = object.Color;
	return *this;
}
UniformBlock::LightSolar & UniformBlock::LightSolar::operator=(const ::LightSolar & object)
{
	Base = object.Base;
	Dir = object.Dir;
	return *this;
}
UniformBlock::LightSpot & UniformBlock::LightSpot::operator=(const ::LightSpot & object)
{
	Base = object.Base;
	Pos = object.Pos;
	Dir = object.Dir;
	Range = object.Range;
	return *this;
}



LightShaderLayout::~LightShaderLayout()
{ }
LightShaderLayout::LightShaderLayout(unsigned int limit)
	: PolyHedraFull::ShaderLayout()
	, Light_Ambient(*this, "Ambient")
	, Light_Solar(*this, "Solar")
	, Light_Spot_Array(*this, "SpotArr", limit)
	, Light_Spot_Count(*this, "SpotCount")
{ }




#include "OpenGL.hpp"

void LightShaderLayout::Find()
{
	LightBlockIndex = glGetUniformBlockIndex(Shader -> ID, "Lights");
	LightBlockBinding = 0;
	glUniformBlockBinding(Shader -> ID, LightBlockIndex, LightBlockBinding);
}
void LightShaderLayout::Create()
{
	LightBuffer = GL::CreateBuffer();
}
void LightShaderLayout::Delete()
{
	GL::DeleteBuffer(LightBuffer);
}
void LightShaderLayout::Put(const LightData & data)
{
	Container::Void void_data;
	void_data.Data = &data;
	void_data.Size = sizeof(LightData);

	GL::BindBuffer(GL::BufferTarget::UniformBuffer, LightBuffer);
	GL::BufferData(GL::BufferTarget::UniformBuffer, void_data.Size, void_data.Data, GL::BufferDataUsage::DynamicDraw);

	glBindBufferBase((unsigned int)GL::BufferTarget::UniformBuffer, LightBlockBinding, LightBuffer);
}

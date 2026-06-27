#include "LightShaderLayout.hpp"

#include "ValueType/Light/Base.hpp"
#include "ValueType/Light/Direction.hpp"
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
PaddedBlock::LightSpot & PaddedBlock::LightSpot::operator=(const ::LightSpot & object)
{
	Base = object.Base;
	Pos = object.Pos;
	Dir = object.Dir;
	Range = object.Range;
	return *this;
}



LightShaderLayout::~LightShaderLayout()
{ }
LightShaderLayout::LightShaderLayout()
	: PolyHedraFull::ShaderLayout()
	, LightBuffer(GL::BufferDataUsage::StreamDraw, 0)
	, LightUniform(*this, "Lights")
{ }



#include "Graphics/Shader/Base.hpp"
#include "OpenGL.hpp"

void LightShaderLayout::BindBlock()
{
	//LightUniform.BindBlock(LightBuffer.Binding);
}
void LightShaderLayout::Create()
{
	LightBuffer.Create();
}
void LightShaderLayout::Delete()
{
	LightBuffer.Delete();
}
void LightShaderLayout::Put(const LightData & data)
{
	Container::Void void_data;
	void_data.Data = &data;
	void_data.Size = sizeof(LightData);

	LightBuffer.DataFull(void_data);
	LightBuffer.BindBase();
}



#include <iostream>
void LightShaderLayout::Info() const
{
	std::cout << "MaxUniformBlockSize" << ' ' << GL::GetIntegerv(GL::ParameterName::MaxUniformBlockSize) << '\n';
	std::cout << "MaxUniformBufferBindings" << ' ' << GL::GetIntegerv(GL::ParameterName::MaxUniformBufferBindings) << '\n';
	std::cout << "MaxUniformLocations" << ' ' << GL::GetIntegerv(GL::ParameterName::MaxUniformLocations) << '\n';
	std::cout << "MaxVertexUniformBlocks" << ' ' << GL::GetIntegerv(GL::ParameterName::MaxVertexUniformBlocks) << '\n';
	std::cout << "MaxFragmentUniformBlocks" << ' ' << GL::GetIntegerv(GL::ParameterName::MaxFragmentUniformBlocks) << '\n';
	std::cout << '\n';
}

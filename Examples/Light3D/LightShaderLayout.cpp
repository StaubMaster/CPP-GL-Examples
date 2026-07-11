#include "LightShaderLayout.hpp"



void LightBufferData::Put(Buffer::Uniform & buffer)
{
	Container::Void void_data;
	void_data.Data = this;
	void_data.Size = sizeof(LightBufferData);

	buffer.DataFull(void_data);
}



LightShaderLayout::~LightShaderLayout()
{ }
LightShaderLayout::LightShaderLayout()
	: PolyHedraFull::ShaderLayout()
	, LightUniform(*this, "ILights")
{ }

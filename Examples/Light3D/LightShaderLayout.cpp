#include "LightShaderLayout.hpp"



LightShaderLayout::~LightShaderLayout()
{ }
LightShaderLayout::LightShaderLayout()
	: PolyHedraFull::ShaderLayout()
	, LightUniform(*this, "ILights")
{ }

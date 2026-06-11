#include "LightShaderLayout.hpp"



LightShaderLayout::~LightShaderLayout()
{ }
LightShaderLayout::LightShaderLayout(unsigned int limit)
	: PolyHedraFull::ShaderLayout()
	, Light_Ambient(*this, "Ambient")
	, Light_Solar(*this, "Solar")
	, Light_Spot_Array(*this, "SpotArr", limit)
	, Light_Spot_Count(*this, "SpotCount")
{ }

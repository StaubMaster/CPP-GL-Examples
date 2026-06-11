#ifndef  LIGHT_SHADER_LAYOUT_HPP
# define LIGHT_SHADER_LAYOUT_HPP

#include "PolyHedra/Graphics/Full/ShaderLayout.hpp"

class LightShaderLayout : public PolyHedraFull::ShaderLayout
{
	public:
	Uniform::LightBase								Light_Ambient;
	Uniform::LightSolar								Light_Solar;
	Uniform::GArray<Uniform::LightSpot, LightSpot>	Light_Spot_Array;
	Uniform::UInt									Light_Spot_Count;

	public:
	~LightShaderLayout();
	LightShaderLayout(unsigned int limit);
};

#endif
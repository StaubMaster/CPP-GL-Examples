#ifndef  LIGHT_SHADER_LAYOUT_HPP
# define LIGHT_SHADER_LAYOUT_HPP

# include "PolyHedra/Graphics/Full/ShaderLayout.hpp"

# include "Graphics/Buffer/Uniform.hpp"
# include "Graphics/Uniform/General/Buffer.hpp"

# include "Graphics/PaddedBlock/LightBase.hpp"
# include "Graphics/PaddedBlock/LightDirection.hpp"
# include "Graphics/PaddedBlock/LightPoint.hpp"
# include "Graphics/PaddedBlock/LightSpot.hpp"
# include "Graphics/PaddedBlock/TypeDefs/UInt.hpp"

struct LightBufferData
{
	PaddedBlock::LightBase			Ambient;
	PaddedBlock::LightDirection		Solar;
	PaddedBlock::UInt				PointCount;
	PaddedBlock::LightPoint			Point[1];
	PaddedBlock::UInt				SpotCount;
	PaddedBlock::LightSpot			Spot[4];
};

class LightShaderLayout : public PolyHedraFull::ShaderLayout
{
	public:
	Uniform::Buffer		LightUniform;

	public:
	~LightShaderLayout();
	LightShaderLayout();
};

#endif
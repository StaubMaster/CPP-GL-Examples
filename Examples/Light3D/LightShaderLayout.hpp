#ifndef  LIGHT_SHADER_LAYOUT_HPP
# define LIGHT_SHADER_LAYOUT_HPP

# include "PolyHedra/Graphics/Full/ShaderLayout.hpp"

# include "ValueType/Vector/F3.hpp"
# include "ValueType/ColorF4.hpp"
# include "ValueType/Range.hpp"

# include "Graphics/Buffer/Base.hpp"
# include "Graphics/Shader/Base.hpp"

namespace UniformBlock
{
	// Padded to be multiple of VectorF4
	struct Float
	{
		float	Value;
		float	Padding[3];
		Float & operator=(const float & object);
	};
	struct UInt
	{
		unsigned int	Value;
		float			Padding[3];
		UInt & operator=(const unsigned int & object);
	};
	struct VectorF3
	{
		::VectorF3	Value;
		float		Padding[1];
		VectorF3 & operator=(const ::VectorF3 & object);
	};
	struct ColorF4
	{
		::ColorF4	Value;
		float		Padding[0];
		ColorF4 & operator=(const ::ColorF4 & object);
	};
	struct Range
	{
		::Range		Value;
		float		Padding[1];
		Range & operator=(const ::Range & object);
	};
	struct LightBase
	{
		Float	Intensity;
		ColorF4	Color;
		LightBase & operator=(const ::LightBase & object);
	};
	struct LightSolar
	{
		LightBase	Base;
		VectorF3	Dir;
		LightSolar & operator=(const ::LightSolar & object);
	};
	struct LightSpot
	{
		LightBase	Base;
		VectorF3	Pos;
		VectorF3	Dir;
		Range		Range;
		LightSpot & operator=(const ::LightSpot & object);
	};
};

class LightShaderLayout : public PolyHedraFull::ShaderLayout
{
	public:
	Uniform::LightBase								Light_Ambient;
	Uniform::LightSolar								Light_Solar;
	Uniform::GArray<Uniform::LightSpot, LightSpot>	Light_Spot_Array;
	Uniform::UInt									Light_Spot_Count;

	public:
	GL::BufferID			LightBuffer;
	GL::UniformLocation		LightLocation;
	GL::UniformLocation		LightBlockIndex;
	GL::UniformLocation		LightBlockBinding;
	struct LightData
	{
		UniformBlock::LightBase		Ambient;
		UniformBlock::LightSolar	Solar;
		UniformBlock::UInt			SpotCount;
		UniformBlock::LightSpot		Spot[4];
	};

	public:
	~LightShaderLayout();
	LightShaderLayout(unsigned int limit);

	public:
	void	Find();
	void	Create();
	void	Delete();
	void	Put(const LightData & data);
};

#endif
#ifndef  LIGHT_SHADER_LAYOUT_HPP
# define LIGHT_SHADER_LAYOUT_HPP

# include "PolyHedra/Graphics/Full/ShaderLayout.hpp"

# include "ValueType/Vector/F3.hpp"
# include "ValueType/ColorF4.hpp"
# include "ValueType/Range.hpp"

# include "Graphics/Buffer/Uniform.hpp"
# include "Graphics/Uniform/General/Buffer.hpp"

namespace PaddedBlock
{
	// Padded to be multiple of VectorF4
	// glsl std140 Interface Block

	template<typename Type, unsigned int PaddingCount>
	struct TypeBase
	{
		Type	Value;
		float	Padding[PaddingCount];
		TypeBase & operator=(const Type & object)
		{
			Value = object;
			return *this;
		}
	};

	typedef TypeBase<float, 3> Float;
	typedef TypeBase<unsigned int, 3> UInt;
	typedef TypeBase<::VectorF3, 1> VectorF3;
	typedef TypeBase<::ColorF4, 0> ColorF4;
	typedef TypeBase<::Range, 1> Range;

	struct LightBase
	{
		PaddedBlock::Float		Intensity;
		PaddedBlock::ColorF4	Color;
		LightBase & operator=(const ::LightBase & object);
	};
	struct LightSolar
	{
		PaddedBlock::LightBase	Base;
		PaddedBlock::VectorF3	Dir;
		LightSolar & operator=(const ::LightSolar & object);
	};
	struct LightSpot
	{
		PaddedBlock::LightBase	Base;
		PaddedBlock::VectorF3	Pos;
		PaddedBlock::VectorF3	Dir;
		PaddedBlock::Range		Range;
		LightSpot & operator=(const ::LightSpot & object);
	};
};

class LightShaderLayout : public PolyHedraFull::ShaderLayout
{
	public:
	Buffer::Uniform			LightBuffer;
	Uniform::Buffer			LightUniform;

	struct LightData
	{
		PaddedBlock::LightBase		Ambient;
		PaddedBlock::LightSolar		Solar;
		PaddedBlock::UInt			SpotCount;
		PaddedBlock::LightSpot		Spot[4];
	};

	public:
	~LightShaderLayout();
	LightShaderLayout();

	public:
	void	BindBlock();
	void	Create();
	void	Delete();
	void	Put(const LightData & data);
	void	Info() const;
};

#endif
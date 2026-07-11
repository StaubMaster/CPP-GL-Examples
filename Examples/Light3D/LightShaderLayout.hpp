#ifndef  LIGHT_SHADER_LAYOUT_HPP
# define LIGHT_SHADER_LAYOUT_HPP

# include "PolyHedra/Graphics/Full/ShaderLayout.hpp"

# include "ValueType/Vector/F3.hpp"
# include "ValueType/Color/F4.hpp"
# include "ValueType/RangeF.hpp"

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
	typedef TypeBase<::RangeF, 1> RangeF;

	struct LightBase
	{
		PaddedBlock::Float		Intensity;
		PaddedBlock::ColorF4	Color;
		LightBase & operator=(const ::LightBase & object);
	};
	struct LightDirection
	{
		PaddedBlock::LightBase	Base;
		PaddedBlock::VectorF3	Dir;
		LightDirection & operator=(const ::LightDirection & object);
	};
	struct LightPoint
	{
		PaddedBlock::LightBase	Base;
		PaddedBlock::VectorF3	Pos;
		LightPoint & operator=(const ::LightPoint & object);
	};
	struct LightSpot
	{
		PaddedBlock::LightBase	Base;
		PaddedBlock::VectorF3	Pos;
		PaddedBlock::VectorF3	Dir;
		PaddedBlock::RangeF		Range;
		LightSpot & operator=(const ::LightSpot & object);
	};
};

# define LIGHT_BINDING 0
struct LightBufferData
{
	PaddedBlock::LightBase			Ambient;
	PaddedBlock::LightDirection		Solar;
	PaddedBlock::UInt				PointCount;
	PaddedBlock::LightPoint			Point[1];
	PaddedBlock::UInt				SpotCount;
	PaddedBlock::LightSpot			Spot[4];

	void	Put(Buffer::Uniform & buffer);
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
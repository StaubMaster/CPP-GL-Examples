#ifndef  UI_TEXT_SHADER_HPP
# define UI_TEXT_SHADER_HPP

# include "Graphics/Uniform/General/Layout.hpp"
# include "Graphics/Uniform/_Include.hpp"
# include "Graphics/Uniform/General/Buffer.hpp"

# include "Graphics/PaddedBlock/TypeDefs/VectorF2.hpp"
# include "Graphics/PaddedBlock/TypeDefs/ColorF4.hpp"
# include "ValueType/Box/F2.hpp"

namespace UI
{

namespace Text
{

struct TextData
{
	BoxF2		Bound;
	ColorF4		Color;
	VectorF2	CharSize;
	float		Padding[2];
};

const static unsigned int	PalletsLimit = 128;
const static unsigned int	TextsLimit = 64;

struct FontBufferData
{
	BoxF2	Array[PalletsLimit];
};
struct TextsBufferData
{
	TextData	Array[TextsLimit];
};

class ShaderLayout : public Uniform::Layout
{
	public:
	Uniform::DisplaySize		DisplaySize;

	Uniform::Buffer		Pallets;
	Uniform::Buffer		Texts;

	public:
	~ShaderLayout();
	ShaderLayout();
};

};

};

#endif
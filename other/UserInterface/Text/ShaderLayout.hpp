#ifndef  UI_TEXT_SHADER_HPP
# define UI_TEXT_SHADER_HPP

#include "Graphics/Uniform/Layout.hpp"
#include "Graphics/Uniform/_Include.hpp"



namespace UI
{

namespace Text
{

class ShaderLayout : public Uniform::Layout
{
	public:
	Uniform::DisplaySize		DisplaySize;

	// make Uniform::BoxF2
	Uniform::VectorF2Array<128>		PalletArrayMin;
	Uniform::VectorF2Array<128>		PalletArrayMax;

	// make this a stuct / custom Uniform
	Uniform::VectorF2Array<32>		TextBoundArrayMin;
	Uniform::VectorF2Array<32>		TextBoundArrayMax;
	Uniform::ColorF4Array<32>		TextColorArray;

	public:
	~ShaderLayout();
	ShaderLayout();
};

};

};

#endif
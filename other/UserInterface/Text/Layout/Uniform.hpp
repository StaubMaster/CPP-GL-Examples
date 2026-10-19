#ifndef  UI_TEXT_LAYOUT_UNIFORM_HPP
# define UI_TEXT_LAYOUT_UNIFORM_HPP

# include "Graphics/Uniform/General/Layout.hpp"
# include "Graphics/Uniform/_Include.hpp"
# include "Graphics/Uniform/General/Buffer.hpp"

namespace UI
{

namespace Text
{

class LayoutUniform : public Uniform::Layout
{
	public:
	Uniform::DisplaySize		DisplaySize;

	Uniform::Buffer		Pallets;
	Uniform::Buffer		Texts;

	public:
	LayoutUniform();
};

};

};

#endif
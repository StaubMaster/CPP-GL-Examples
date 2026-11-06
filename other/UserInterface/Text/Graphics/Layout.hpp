#ifndef  UI_TEXT_GRAPHICS_LAYOUT_HPP
# define UI_TEXT_GRAPHICS_LAYOUT_HPP

# include "Graphics/Uniform/General/Layout.hpp"
# include "Graphics/Uniform/_Include.hpp"
# include "Graphics/Uniform/General/Buffer.hpp"

namespace UI
{
namespace Text
{
struct Layout : public Uniform::Layout
{
	Uniform::DisplaySize		DisplaySize;

	Uniform::Buffer		Pallets;
	Uniform::Buffer		Texts;

	Layout();
};
};
};

#endif
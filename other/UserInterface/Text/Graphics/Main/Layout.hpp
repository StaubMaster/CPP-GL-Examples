#ifndef  UI_TEXT_GRAPHICS_MAIN_LAYOUT_HPP
# define UI_TEXT_GRAPHICS_MAIN_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace UI
{
namespace Text
{
namespace Main
{
struct Layout : public ::Attribute::Layout
{
	::Attribute::VectorF2	Pos;
	Layout();
};
};
};
};

#endif
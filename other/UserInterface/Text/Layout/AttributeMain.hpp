#ifndef  UI_TEXT_LAYOUT_ATTRIBUTE_MAIN_HPP
# define UI_TEXT_LAYOUT_ATTRIBUTE_MAIN_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace UI
{

namespace Text
{

class LayoutAttributeMain : public ::Attribute::Layout
{
	public:
	::Attribute::VectorF2	Pos;
	public:
	LayoutAttributeMain();
};

};

};

#endif
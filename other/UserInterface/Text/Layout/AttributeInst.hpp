#ifndef  UI_TEXT_LAYOUT_ATTRIBUTE_INST_HPP
# define UI_TEXT_LAYOUT_ATTRIBUTE_INST_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace UI
{

namespace Text
{

class LayoutAttributeInst : public ::Attribute::Layout
{
	public:
	::Attribute::VectorF2	TextPos;
	::Attribute::UInt		CharIdx;
	::Attribute::UInt		TextIdx;
	public:
	LayoutAttributeInst();
};

};

};

#endif
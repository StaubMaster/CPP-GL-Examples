#ifndef  UI_TEXT_GRAPHICS_INST_LAYOUT_HPP
# define UI_TEXT_GRAPHICS_INST_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/_Include.hpp"

namespace UI
{
namespace Text
{
namespace Inst
{
struct Layout : public ::Attribute::Layout
{
	::Attribute::VectorF2	TextPos;
	::Attribute::UInt		CharIdx;
	::Attribute::UInt		TextIdx;
	Layout();
};
};
};
};

#endif
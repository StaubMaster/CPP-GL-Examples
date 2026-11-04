#ifndef  UI_CONTROL_GRAPHICS_INST_LAYOUT_HPP
# define UI_CONTROL_GRAPHICS_INST_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/TypeDefs/Float.hpp"
# include "Graphics/Attribute/TypeDefs/ColorF4.hpp"
# include "Graphics/Attribute/BoxF2.hpp"

namespace UI
{
namespace Control
{
namespace Inst
{
class Layout : public ::Attribute::Layout
{
	public:
	::Attribute::BoxF2		Box;
	::Attribute::Float		Layer;
	::Attribute::ColorF4	Color;
	::Attribute::BoxF2		Bound;
	public:
	Layout();
};
};
};
};

#endif
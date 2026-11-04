#ifndef  UI_CONTROL_GRAPHICS_MAIN_LAYOUT_HPP
# define UI_CONTROL_GRAPHICS_MAIN_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/TypeDefs/VectorF2.hpp"

namespace UI
{
namespace Control
{
namespace Main
{
class Layout : public ::Attribute::Layout
{
	public:
	::Attribute::VectorF2	Pos;
	public:
	Layout();
};
};
};
};

#endif
#ifndef  POLYGON_GRAPHICS_FULL_MAIN_LAYOUT_HPP
# define POLYGON_GRAPHICS_FULL_MAIN_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/TypeDefs/VectorF2.hpp"
# include "Graphics/Attribute/TypeDefs/ColorF4.hpp"

namespace PolyGonFull
{
namespace Main
{
class Layout : public ::Attribute::Layout
{
	public:
	::Attribute::VectorF2	Pos;
	::Attribute::ColorF4	Col;
	public:
	~Layout();
	Layout();
	Layout(const Layout & other);
};
};
};

#endif
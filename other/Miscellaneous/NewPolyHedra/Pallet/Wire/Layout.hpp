#ifndef  NEW_POLYHEDRA_PALLET_WIRE_LAYOUT_HPP
# define NEW_POLYHEDRA_PALLET_WIRE_LAYOUT_HPP

# include "Graphics/Attribute/General/Layout.hpp"
# include "Graphics/Attribute/TypeDefs/VectorF3.hpp"
# include "Graphics/Attribute/TypeDefs/ColorF4.hpp"

namespace NewPolyHedra
{
namespace PalletWire
{
class Layout : public ::Attribute::Layout
{
	public:
	::Attribute::VectorF3	Pos;
	::Attribute::ColorF4	Col;
	public:
	~Layout();
	Layout();
	Layout(const Layout & other);
};
};
};

#endif
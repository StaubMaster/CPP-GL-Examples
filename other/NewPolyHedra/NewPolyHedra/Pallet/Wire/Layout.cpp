#include "NewPolyHedra/Pallet/Wire/Layout.hpp"
#include "NewPolyHedra/Pallet/Wire/Data.hpp"



NewPolyHedra::PalletWire::Layout::~Layout() { }
NewPolyHedra::PalletWire::Layout::Layout()
	: ::Attribute::Layout(0, sizeof(NewPolyHedra::PalletWire::Data))
	, Pos(*this)
	, Col(*this)
{ }
NewPolyHedra::PalletWire::Layout::Layout(const Layout & other)
	: ::Attribute::Layout(other)
	, Pos(*this, other.Pos)
	, Col(*this, other.Col)
{ }

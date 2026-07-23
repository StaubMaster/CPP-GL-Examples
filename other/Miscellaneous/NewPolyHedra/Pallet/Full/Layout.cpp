#include "NewPolyHedra/Pallet/Full/Layout.hpp"
#include "NewPolyHedra/Pallet/Full/Data.hpp"



NewPolyHedra::PalletFull::Layout::~Layout() { }
NewPolyHedra::PalletFull::Layout::Layout()
	: ::Attribute::Layout(0, sizeof(NewPolyHedra::PalletFull::Data))
	, Position(*this)
	, Normal(*this)
	, Texture(*this)
{ }
NewPolyHedra::PalletFull::Layout::Layout(const Layout & other)
	: ::Attribute::Layout(other)
	, Position(*this, other.Position)
	, Normal(*this, other.Normal)
	, Texture(*this, other.Texture)
{ }

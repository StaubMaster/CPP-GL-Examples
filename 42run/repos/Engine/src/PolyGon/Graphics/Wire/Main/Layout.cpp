#include "PolyGon/Graphics/Wire/Main/Layout.hpp"
#include "PolyGon/PolyGon.hpp"



PolyGonWire::Main::Layout::~Layout() { }
PolyGonWire::Main::Layout::Layout()
	: ::Attribute::Layout(0, sizeof(PolyGon::Corner))
	, Pos(*this)
	, Col(*this)
{ }
PolyGonWire::Main::Layout::Layout(const Layout & other)
	: ::Attribute::Layout(other)
	, Pos(*this, other.Pos)
	, Col(*this, other.Col)
{ }

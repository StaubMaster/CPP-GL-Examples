#include "PolyGon/Graphics/Full/Main/Layout.hpp"
#include "PolyGon/Graphics/Full/Main/Data.hpp"



PolyGonFull::Main::Layout::~Layout() { }
PolyGonFull::Main::Layout::Layout()
	: ::Attribute::Layout(0, sizeof(Main::Data))
	, Pos(*this)
	, Col(*this)
{ }
PolyGonFull::Main::Layout::Layout(const Layout & other)
	: ::Attribute::Layout(other)
	, Pos(*this, other.Pos)
	, Col(*this, other.Col)
{ }

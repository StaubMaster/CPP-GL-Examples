#include "Layout.hpp"
#include "Data.hpp"



UI::ControlGraphics::Main::Layout::Layout()
	: ::Attribute::Layout(0, sizeof(Data))
	, Pos(*this)
{ }

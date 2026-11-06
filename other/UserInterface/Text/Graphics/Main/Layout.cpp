#include "Layout.hpp"
#include "Data.hpp"



UI::Text::Main::Layout::Layout()
	: ::Attribute::Layout(0, sizeof(Data))
	, Pos(*this)
{ }

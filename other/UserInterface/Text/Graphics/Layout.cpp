#include "Layout.hpp"



UI::Text::Layout::Layout()
	: Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
	, Pallets(*this, "IPallets")
	, Texts(*this, "ITexts")
{ }

#include "Text/Layout/Uniform.hpp"



UI::Text::LayoutUniform::LayoutUniform()
	: Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
	, Pallets(*this, "IPallets")
	, Texts(*this, "ITexts")
{ }

#include "ShaderLayout.hpp"



UI::Text::ShaderLayout::~ShaderLayout()
{ }
UI::Text::ShaderLayout::ShaderLayout()
	: Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
	, Pallets(*this, "IPallets")
	, Texts(*this, "ITexts")
{ }

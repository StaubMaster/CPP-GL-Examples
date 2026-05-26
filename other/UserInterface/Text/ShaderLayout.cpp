#include "ShaderLayout.hpp"



UI::Text::ShaderLayout::~ShaderLayout() { }

UI::Text::ShaderLayout::ShaderLayout()
	: Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
	, PalletArrayMin(*this, "PalletArrayMin")
	, PalletArrayMax(*this, "PalletArrayMax")
	, TextBoundArrayMin(*this, "TextBoundArrayMin")
	, TextBoundArrayMax(*this, "TextBoundArrayMax")
	, TextColorArray(*this, "TextColorArray")
{ }

#include "Layout.hpp"



UI::Control::ShaderLayout::ShaderLayout()
	: Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
{ }

#include "Layout.hpp"



UI::ControlGraphics::ShaderLayout::ShaderLayout()
	: Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
{ }

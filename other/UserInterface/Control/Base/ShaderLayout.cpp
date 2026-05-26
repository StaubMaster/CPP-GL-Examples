#include "ShaderLayout.hpp"



UI::Control::ShaderLayout::~ShaderLayout()
{ }
UI::Control::ShaderLayout::ShaderLayout()
	: Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
{ }

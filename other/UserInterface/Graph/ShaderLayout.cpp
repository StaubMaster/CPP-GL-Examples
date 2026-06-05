#include "ShaderLayout.hpp"



UI::Graph::ShaderLayout::~ShaderLayout()
{ }
UI::Graph::ShaderLayout::ShaderLayout()
	: Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
{ }

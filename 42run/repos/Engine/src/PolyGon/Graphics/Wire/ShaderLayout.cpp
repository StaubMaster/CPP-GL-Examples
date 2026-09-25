#include "PolyGon/Graphics/Wire/ShaderLayout.hpp"



PolyGonWire::ShaderLayout::~ShaderLayout()
{ }
PolyGonWire::ShaderLayout::ShaderLayout()
	: ::Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Scale(*this, "Scale")
{ }

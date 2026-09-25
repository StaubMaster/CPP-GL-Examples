#include "PolyGon/Graphics/Full/ShaderLayout.hpp"



PolyGonFull::ShaderLayout::~ShaderLayout()
{ }
PolyGonFull::ShaderLayout::ShaderLayout()
	: Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Scale(*this, "Scale")
{ }

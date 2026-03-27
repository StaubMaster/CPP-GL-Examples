#include "Grid2D/Graphics/Shader.hpp"



Grid2DGraphics::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Scale(*this, "Scale")
{ }

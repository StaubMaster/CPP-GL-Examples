#include "Layout/Shader.hpp"



ShaderLayoutDisplay::~ShaderLayoutDisplay()
{ }
ShaderLayoutDisplay::ShaderLayoutDisplay()
	: ::Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
{ }



ShaderLayoutView3D::~ShaderLayoutView3D()
{ }
ShaderLayoutView3D::ShaderLayoutView3D()
	: ShaderLayoutDisplay()
	, View(*this, "View")
	, Depth(*this, "Depth")
	, FOV(*this, "FOV")
{ }

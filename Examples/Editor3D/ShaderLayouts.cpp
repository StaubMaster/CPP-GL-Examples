#include "ShaderLayouts.hpp"



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



ShaderLayoutLight3D::~ShaderLayoutLight3D()
{ }
ShaderLayoutLight3D::ShaderLayoutLight3D()
	: ShaderLayoutView3D()
	, LightUniform(*this, "ILights")
{ }

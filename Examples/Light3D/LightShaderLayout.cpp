#include "LightShaderLayout.hpp"



ShaderLayoutView3D::~ShaderLayoutView3D()
{ }
ShaderLayoutView3D::ShaderLayoutView3D()
	: ::Uniform::Layout()
	, DisplaySize(*this, "DisplaySize")
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

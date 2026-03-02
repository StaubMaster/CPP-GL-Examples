#include "WireFrame2D/Shader.hpp"



Wire2D::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this,"DisplaySize")
	, View(*this,"View")
	, Scale(*this,"Scale")
{ }

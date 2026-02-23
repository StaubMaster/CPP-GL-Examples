#include "WireFrame2D/Shader.hpp"



Wire2D::Shader::Shader()
	: ::Shader::Base()
	, WindowSize(*this,"WindowSize")
	, View(*this,"View")
	, Scale(*this,"Scale")
{ }

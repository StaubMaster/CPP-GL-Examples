#include "Arrow2D/Shader.hpp"



Arrow2D::Shader::Shader()
	: ::Shader::Base()
	, WindowSize(*this,"WindowSize")
	, View(*this,"View")
	, Scale(*this,"Scale")
{ }

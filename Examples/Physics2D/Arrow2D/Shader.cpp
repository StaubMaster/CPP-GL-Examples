#include "Arrow2D/Shader.hpp"



Arrow2D::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this,"DisplaySize")
	, View(*this,"View")
	, Scale(*this,"Scale")
{ }

#include "Graphics2D/Wire/Shader.hpp"



Graphics2D::Wire::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this,"DisplaySize")
	, View(*this,"View")
	, Scale(*this,"Scale")
{ }

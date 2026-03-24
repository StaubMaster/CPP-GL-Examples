#include "PolyGon/Graphics/Wire/Shader.hpp"



PolyGon::Wire::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this,"DisplaySize")
	, View(*this,"View")
	, Scale(*this,"Scale")
{ }

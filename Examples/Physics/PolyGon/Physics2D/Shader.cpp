#include "PolyGon/Physics2D/Shader.hpp"



Physics2D::Shader::Shader()
	: ::Shader::Base()
	, WindowSize(*this, "WindowSize")
	, View(*this, "View")
	, Scale(*this, "Scale")
{ }

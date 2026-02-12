#include "Shader.hpp"



Physics2D::Shader::Shader()
	: ::Shader::Base(),
	WindowSize(Uniform::NameShader("WindowSize", *this))
{ }

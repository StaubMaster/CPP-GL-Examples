#include "Shader.hpp"



Physics2D::Shader::Shader()
	: ::Shader::Base()
	, WindowSize(Uniform::NameShader("WindowSize", *this))
	, ViewPos(Uniform::NameShader("ViewPos", *this))
	, ViewScale(Uniform::NameShader("ViewScale", *this))
{ }

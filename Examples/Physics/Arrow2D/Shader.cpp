#include "Arrow2D/Shader.hpp"



Arrow2D::Shader::Shader()
	: ::Shader::Base()
	, WindowSize(Uniform::NameShader("WindowSize", *this))
	, View(Uniform::NameShader("View", *this))
	, Scale(Uniform::NameShader("Scale", *this))
{ }

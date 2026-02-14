#include "PolyGon/Physics2D/Shader.hpp"



Physics2D::Shader::Shader()
	: ::Shader::Base()
	, WindowSize(Uniform::NameShader("WindowSize", *this))
	, View(Uniform::NameShader("View", *this))
	, Scale(Uniform::NameShader("Scale", *this))
{ }

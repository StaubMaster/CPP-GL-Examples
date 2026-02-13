#include "Shader.hpp"



Physics2D::Shader::Shader()
	: ::Shader::Base()
	, WindowSize(Uniform::NameShader("WindowSize", *this))
	, ViewPos(Uniform::NameShader("View.Pos", *this))
	, ViewRot(Uniform::NameShader("View.Rot", *this))
	, ViewScale(Uniform::NameShader("Scale", *this))
{ }

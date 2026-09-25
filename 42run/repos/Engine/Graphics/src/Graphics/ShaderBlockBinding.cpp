#include "Graphics/ShaderBlockBinding.hpp"
#include "Graphics/Shader/Base.hpp"



ShaderBlockBinding::~ShaderBlockBinding()
{ }

ShaderBlockBinding::ShaderBlockBinding(::Shader::Base & shader, GL::BlockBinding binding)
	: Shader(shader)
	, Binding(binding)
{ }



void ShaderBlockBinding::Bind(GL::BlockIndex index)
{
	Shader.BindUniformBlockIndex(index, Binding);
}

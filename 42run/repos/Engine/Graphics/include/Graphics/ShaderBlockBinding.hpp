#ifndef  SHADER_BLOCK_BINDING_HPP
# define SHADER_BLOCK_BINDING_HPP

# include "OpenGLTypes.hpp"

namespace Shader { class Base; };

struct ShaderBlockBinding
{
	::Shader::Base &		Shader;
	GL::BlockBinding		Binding;

	~ShaderBlockBinding();
	ShaderBlockBinding() = delete;

	ShaderBlockBinding(::Shader::Base & shader, GL::BlockBinding binding);

	void	Bind(GL::BlockIndex index);
};

#endif
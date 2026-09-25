#include "Graphics/Uniform/General/Buffer.hpp"
#include "Graphics/Uniform/General/Layout.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/ShaderBlockBinding.hpp"



Uniform::Buffer::Buffer(std::string name, bool is_dynamic)
	: Uniform::Base(name, is_dynamic)
	, Index(-1)
{ }
Uniform::Buffer::Buffer(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: Uniform::Base(layout, name, is_dynamic)
	, Index(-1)
{ }



void Uniform::Buffer::Find(Shader::Base & shader)
{
	Index = shader.FindUniformBlockIndex(Name.c_str());
}



void Uniform::Buffer::PutVoid(const void * val)
{
	ShaderBlockBinding * shader_block_binding = (ShaderBlockBinding *)val;
	shader_block_binding -> Bind(Index);
}

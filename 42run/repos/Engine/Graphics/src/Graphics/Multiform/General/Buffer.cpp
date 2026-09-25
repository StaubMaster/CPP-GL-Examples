#include "Graphics/Multiform/General/Buffer.hpp"

#include "Graphics/Uniform/General/Base.hpp"
#include "Graphics/ShaderBlockBinding.hpp"



Multiform::Buffer::~Buffer()
{ }
Multiform::Buffer::Buffer(std::string name)
	: Base(name)
{ }



void Multiform::Buffer::PutData(Uniform::Base & uniform)
{
	(void)uniform;
}
void Multiform::Buffer::PutData(Uniform::Base & uniform, Shader::Base & shader)
{
	ShaderBlockBinding shader_block_binding(shader, Binding);
	uniform.PutVoid(&shader_block_binding);
}
void Multiform::Buffer::ChangeData(GL::BlockBinding binding)
{
	Binding = binding;
	PutUniformThis();
}

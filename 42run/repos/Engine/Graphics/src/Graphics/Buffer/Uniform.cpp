#include "Graphics/Buffer/Uniform.hpp"
#include "OpenGL.hpp"



Buffer::Uniform::~Uniform() { }
Buffer::Uniform::Uniform(GL::BufferDataUsage usage)
	: Buffer::Base(GL::BufferTarget::UniformBuffer, usage)
{ }



void Buffer::Uniform::BindBase(GL::BlockBinding binding)
{
	GL::BindBufferBase(Target, binding, ID);
}

#ifndef  PHYSICS_2D_BUFFER_ARRAY_HPP
# define PHYSICS_2D_BUFFER_ARRAY_HPP

# include "Graphics/Buffer/ArrayBase.hpp"
# include "Main/Buffer.hpp"
# include "Inst/Buffer.hpp"
# include "OpenGLTypes.hpp"

namespace Physics2D
{
class BufferArray : public ::BufferArray::Base
{
	public:
	Physics2D::Main::Buffer	Main;
	Physics2D::Inst::Buffer	Inst;
	GL::DrawMode			DrawMode;
	public:
	BufferArray();
	public:
	void Draw();
};
};

#endif
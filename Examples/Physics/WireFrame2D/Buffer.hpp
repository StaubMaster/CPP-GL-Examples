#ifndef  WIRE_2D_BUFFER_ARRAY_HPP
# define WIRE_2D_BUFFER_ARRAY_HPP

# include "Graphics/Buffer/MainInst.hpp"
# include "WireFrame2D/Main/Buffer.hpp"
# include "Physics2D/Inst/Buffer.hpp"

# include "OpenGLTypes.hpp"

namespace Wire2D
{
class Buffer : public ::BufferArray::MainInst
{
	public:
	WireFrame2D::Main::Buffer	Main;
	Physics2D::Inst::Buffer		Inst;

	public:
	~Buffer();
	Buffer();
};
};

#endif
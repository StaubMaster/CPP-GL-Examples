#ifndef  WIRE_2D_BUFFER_ARRAY_HPP
# define WIRE_2D_BUFFER_ARRAY_HPP

# include "Graphics/Buffer/MainElemInst.hpp"
# include "WireFrame2D/Main/Buffer.hpp"
# include "Graphics2D/Inst/Buffer.hpp"

# include "OpenGLTypes.hpp"

namespace Wire2D
{
typedef BufferArray::MainElemInst<
	Wire2D::Main::Buffer,
	Wire2D::Elem::Buffer,
	Graphics2D::Inst::Buffer
> Buffer;

/*class Buffer : public ::BufferArray::MainElemInst<
	Wire2D::Main::Buffer,
	Wire2D::Elem::Buffer,
	Physics2D::Inst::Buffer
>
{
	public:
	~Buffer();
	Buffer();
};*/
};

#endif
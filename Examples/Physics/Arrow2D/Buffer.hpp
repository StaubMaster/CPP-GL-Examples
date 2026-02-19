#ifndef  ARROW_2D_BUFFER_ARRAY_HPP
# define ARROW_2D_BUFFER_ARRAY_HPP

# include "Graphics/Buffer/MainInst.hpp"
# include "Arrow2D/Main/Buffer.hpp"
# include "Arrow2D/Inst/Buffer.hpp"

# include "OpenGLTypes.hpp"

namespace Arrow2D
{
class Buffer : public ::BufferArray::MainInst
{
	public:
	Arrow2D::Main::Buffer	Main;
	Arrow2D::Inst::Buffer	Inst;

	public:
	~Buffer();
	Buffer();
};
};

#endif
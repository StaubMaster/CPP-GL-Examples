#ifndef  POLYGON_GRAPHICS_FULL_BUFFER_HPP
# define POLYGON_GRAPHICS_FULL_BUFFER_HPP

# include "Graphics/Buffer/MainInst.hpp"
# include "PolyGon/Graphics/Full/Main/Buffer.hpp"
# include "Inst2D/Buffer.hpp"

# include "OpenGLTypes.hpp"

namespace PolyGon
{
namespace Full
{
typedef ::BufferArray::MainInst<
	PolyGon::Full::Main::Buffer,
	Inst2D::Buffer
> Buffer;
};
};

#endif
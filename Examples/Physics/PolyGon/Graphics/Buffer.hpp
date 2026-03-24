#ifndef  POLYGON_GRAPHICS_BUFFER_HPP
# define POLYGON_GRAPHICS_BUFFER_HPP

# include "Graphics/Buffer/MainInst.hpp"
# include "PolyGon/Graphics/Full/Buffer.hpp"
# include "Inst2D/Buffer.hpp"

# include "OpenGLTypes.hpp"

namespace PolyGon
{
typedef ::BufferArray::MainInst<
	PolyGon::Full::Buffer,
	Inst2D::Buffer
> Buffer;
};

#endif
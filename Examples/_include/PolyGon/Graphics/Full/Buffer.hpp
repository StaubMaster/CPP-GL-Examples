#ifndef  POLYGON_GRAPHICS_FULL_BUFFER_HPP
# define POLYGON_GRAPHICS_FULL_BUFFER_HPP

# include "Graphics/Buffer/MainInst.hpp"
# include "PolyGon/Graphics/Full/Main/Buffer.hpp"
# include "Instance/Basic2D/Buffer.hpp"

# include "OpenGLTypes.hpp"

namespace PolyGonFull
{
typedef ::BufferArray::MainInst<
	PolyGonFull::Main::Buffer,
	Instance::Basic2D::Buffer
> Buffer;
};

#endif
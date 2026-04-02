#ifndef  POLYHEDRA_GRAPHICS_FULL_BUFFER_HPP
# define POLYHEDRA_GRAPHICS_FULL_BUFFER_HPP

# include "Graphics/Buffer/MainInst.hpp"
# include "PolyHedra/Graphics/Full/Main/Buffer.hpp"
# include "Instance/Basic3D/Buffer.hpp"

# include "OpenGLTypes.hpp"

namespace PolyHedraFull
{
typedef ::BufferArray::MainInst<
	PolyHedraFull::Main::Buffer,
	Instance::Basic3D::Buffer
> Buffer;
};

#endif
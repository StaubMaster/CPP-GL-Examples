#ifndef  POLYGON_GRAPHICS_WIRE_BUFFER_HPP
# define POLYGON_GRAPHICS_WIRE_BUFFER_HPP

# include "Graphics/Buffer/MainElemInst.hpp"
# include "PolyGon/Graphics/Wire/Main/Buffer.hpp"
# include "Inst2D/Buffer.hpp"

# include "OpenGLTypes.hpp"

namespace PolyGon
{
namespace Wire
{
typedef ::BufferArray::MainElemInst<
	PolyGon::Wire::Main::Buffer,
	PolyGon::Wire::Elem::Buffer,
	Inst2D::Buffer
> Buffer;
};
};

#endif
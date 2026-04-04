#ifndef  POLYGON_GRAPHICS_WIRE_BUFFER_HPP
# define POLYGON_GRAPHICS_WIRE_BUFFER_HPP

# include "Graphics/Buffer/MainElemInst.hpp"
# include "PolyGon/Graphics/Wire/Main/Buffer.hpp"
# include "PolyGon/Graphics/Wire/Elem/Buffer.hpp"
# include "Instance/Basic2D/Buffer.hpp"

namespace PolyGonWire
{
typedef ::BufferArray::MainElemInst<
	PolyGonWire::Main::Buffer,
	PolyGonWire::Elem::Buffer,
	Instance::Basic2D::Buffer
> Buffer;
};

#endif
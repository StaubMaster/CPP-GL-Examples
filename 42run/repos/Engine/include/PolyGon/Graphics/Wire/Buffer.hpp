#ifndef  POLYGON_GRAPHICS_WIRE_BUFFER_HPP
# define POLYGON_GRAPHICS_WIRE_BUFFER_HPP

# include "Graphics/VertexArray/MainElemInst.hpp"

namespace PolyGonWire
{
typedef ::VertexArray::MainElemInst Buffer;
/*typedef ::VertexArray::MainElemInst<
	GL::BufferDataUsage::StaticDraw,
	GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt,
	GL::BufferDataUsage::StaticDraw,
	GL::DrawMode::Lines
> Buffer;*/
};

#endif
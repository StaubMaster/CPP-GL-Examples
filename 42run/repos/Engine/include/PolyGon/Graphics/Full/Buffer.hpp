#ifndef  POLYGON_GRAPHICS_FULL_BUFFER_HPP
# define POLYGON_GRAPHICS_FULL_BUFFER_HPP

# include "Graphics/VertexArray/MainInst.hpp"

namespace PolyGonFull
{
typedef ::VertexArray::MainInst Buffer;
/*typedef ::VertexArray::MainInst<
	GL::BufferDataUsage::StaticDraw,
	GL::BufferDataUsage::StreamDraw,
	GL::DrawMode::Triangles
> Buffer;*/
};

#endif
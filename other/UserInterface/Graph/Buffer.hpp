#ifndef  UI_GRAPH_BUFFER_HPP
# define UI_GRAPH_BUFFER_HPP

# include "Graphics/Buffer/Main.hpp"

namespace UI
{

namespace Graph
{

typedef ::VertexArray::Main<
	GL::BufferDataUsage::StreamDraw,
	GL::DrawMode::Lines
> Buffer;

};

};

#endif
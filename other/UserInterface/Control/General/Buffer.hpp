#ifndef  UI_CONTROL_BUFFER_HPP
# define UI_CONTROL_BUFFER_HPP

# include "Graphics/Buffer/MainInst.hpp"

namespace UI
{

namespace Control
{

typedef ::BufferArray::MainInst<
	GL::BufferDataUsage::StaticDraw,
	GL::BufferDataUsage::StreamDraw,
	GL::DrawMode::Triangles
> Buffer;

};

};

#endif
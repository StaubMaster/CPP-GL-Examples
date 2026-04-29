#include "Grid2D/Graphics/Main/Buffer.hpp"
#include "Grid2D/Graphics/Main/Data.hpp"
#include "OpenGLTypes.hpp"



Grid2DGraphics::Main::Buffer::~Buffer() { }
Grid2DGraphics::Main::Buffer::Buffer(VertexArray & vertex_array)
	: ::Buffer::Array(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(Main::Data))
	, Pos()
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);
}

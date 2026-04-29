#include "Grid2D/Graphics/Inst/Buffer.hpp"
#include "Grid2D/Graphics/Inst/Data.hpp"
#include "OpenGLTypes.hpp"



Grid2DGraphics::Inst::Buffer::~Buffer() { }
Grid2DGraphics::Inst::Buffer::Buffer(VertexArray & vertex_array)
	: ::Buffer::Array(buffer_array, GL::BufferDataUsage::StaticDraw, 1, sizeof(Inst::Data))
	, Pos()
	, Size()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Size);
}

#include "Arrow2D/Inst/Buffer.hpp"
#include "Arrow2D/Inst/Data.hpp"

#include "OpenGL.hpp"



Arrow2D::Inst::Buffer::Buffer(VertexArray & vertex_array)
	: ::Buffer::Array(buffer_array, GL::BufferDataUsage::StreamDraw, 1, sizeof(Data))
	, Pos0()
	, Pos1()
	, Size()
	, Col()
{
	Attributes.Allocate(4, 0);
	Attributes.Insert(&Pos0);
	Attributes.Insert(&Pos1);
	Attributes.Insert(&Size);
	Attributes.Insert(&Col);
}

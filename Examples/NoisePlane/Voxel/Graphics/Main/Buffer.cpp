#include "Buffer.hpp"
#include "Data.hpp"



VoxelGraphics::MainBuffer::~MainBuffer() { }
VoxelGraphics::MainBuffer::MainBuffer(::VertexArray & vertex_array)
	: ::Buffer::Array(vertex_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(MainData))
	, Pos()
	, Tex()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Tex);
}

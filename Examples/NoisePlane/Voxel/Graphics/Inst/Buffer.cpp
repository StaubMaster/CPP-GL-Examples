#include "Buffer.hpp"
#include "Data.hpp"



VoxelGraphics::InstBuffer::~InstBuffer() { }
VoxelGraphics::InstBuffer::InstBuffer(::VertexArray & vertex_array)
	: ::Buffer::Array(vertex_array, GL::BufferDataUsage::StaticDraw, 1, sizeof(InstData))
	, Pos(*this)
{ }

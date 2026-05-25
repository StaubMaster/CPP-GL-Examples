#include "Buffer.hpp"
#include "Data.hpp"



VoxelGraphics::InstBuffer::~InstBuffer() { }
VoxelGraphics::InstBuffer::InstBuffer(::VertexArray & vertex_array)
	: ::Buffer::Array(vertex_array, GL::BufferDataUsage::StaticDraw)
{ }

VoxelGraphics::InstLayout::~InstLayout() { }
VoxelGraphics::InstLayout::InstLayout()
	: ::Attribute::Layout(1, sizeof(InstData))
	, Pos(*this)
{ }

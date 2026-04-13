#include "Buffer.hpp"
#include "Data.hpp"



VoxelGraphics::InstBuffer::~InstBuffer() { }
VoxelGraphics::InstBuffer::InstBuffer(::BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 1, sizeof(InstData))
	, Pos()
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);
}

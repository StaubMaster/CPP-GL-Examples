#include "Buffer.hpp"
#include "Data.hpp"



VoxelGraphics::MainBuffer::~MainBuffer() { }
VoxelGraphics::MainBuffer::MainBuffer(::BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(MainData))
	, Pos()
	, Col()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Col);
}

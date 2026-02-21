#include "Inst/Physics2D/Buffer.hpp"
#include "Inst/Physics2D/Data.hpp"

#include "OpenGL.hpp"



Physics2D::Inst::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StreamDraw, 1, sizeof(Data))
	, Now()
	, Vel()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Now);
	Attributes.Insert(&Vel);
}

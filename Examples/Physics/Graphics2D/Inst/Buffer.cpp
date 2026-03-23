#include "Graphics2D/Inst/Buffer.hpp"
#include "ValueType/Trans2D.hpp"

#include "OpenGL.hpp"



Graphics2D::Inst::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StreamDraw, 1, sizeof(Trans2D))
	, Now()
{
	Attributes.Allocate(1);
	Attributes.Insert(&Now);
}

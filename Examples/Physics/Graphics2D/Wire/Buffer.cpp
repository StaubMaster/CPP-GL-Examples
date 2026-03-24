#include "Graphics2D/Wire/Buffer.hpp"
#include "WireFrame2D/WireFrame2D.hpp"
#include "OpenGL.hpp"



Graphics2D::Wire::Main::Buffer::~Buffer() { }
Graphics2D::Wire::Main::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(WireFrame2D::Corner))
	, Pos()
	, Col()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Col);
}



Graphics2D::Wire::Elem::Buffer::~Buffer() { }
Graphics2D::Wire::Elem::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Element(buffer_array, GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt)
{ }

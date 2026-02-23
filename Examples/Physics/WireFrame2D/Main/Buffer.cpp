#include "WireFrame2D/Main/Buffer.hpp"
#include "WireFrame2D/WireFrame2D.hpp"
#include "OpenGL.hpp"



Wire2D::Main::Buffer::~Buffer() { }
Wire2D::Main::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(WireFrame2D::Corner))
	, Pos()
	, Col()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Col);
}

Wire2D::Elem::Buffer::~Buffer() { }
Wire2D::Elem::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Base(buffer_array, GL::BufferTarget::ElementArrayBuffer)
{ }

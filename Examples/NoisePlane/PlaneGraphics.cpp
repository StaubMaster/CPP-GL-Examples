#include "PlaneGraphics.hpp"



PlaneGraphics::MainBuffer::~MainBuffer() { }
PlaneGraphics::MainBuffer::MainBuffer(::BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(MainData))
	, Pos()
	, Col()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Col);
}



PlaneGraphics::InstBuffer::~InstBuffer() { }
PlaneGraphics::InstBuffer::InstBuffer(::BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 1, sizeof(InstData))
	, Pos()
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);
}



PlaneGraphics::Buffer::~Buffer() { }
PlaneGraphics::Buffer::Buffer()
	: ::BufferArray::MainInst<MainBuffer, InstBuffer>(GL::DrawMode::Triangles)
{ }



PlaneGraphics::Shader::~Shader() { }
PlaneGraphics::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Depth(*this, "Depth")
	, FOV(*this, "FOV")
{ }

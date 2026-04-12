#include "ChunkGraphics.hpp"



ChunkGraphics::MainBuffer::~MainBuffer() { }
ChunkGraphics::MainBuffer::MainBuffer(::BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(MainData))
	, Pos()
	, Col()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Col);
}



ChunkGraphics::InstBuffer::~InstBuffer() { }
ChunkGraphics::InstBuffer::InstBuffer(::BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 1, sizeof(InstData))
	, Pos()
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);
}



ChunkGraphics::Buffer::~Buffer() { }
ChunkGraphics::Buffer::Buffer()
	: ::BufferArray::MainInst<MainBuffer, InstBuffer>(GL::DrawMode::Triangles)
{ }



ChunkGraphics::Shader::~Shader() { }
ChunkGraphics::Shader::Shader()
	: ::Shader::Base()
	, DisplaySize(*this, "DisplaySize")
	, View(*this, "View")
	, Depth(*this, "Depth")
	, FOV(*this, "FOV")
{ }

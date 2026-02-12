#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL.hpp"



Physics2D::Main::Buffer::Buffer(
	unsigned int indexPos,
	unsigned int indexCol
) :
	::Buffer::Attribute(GL::BufferTarget::ArrayBuffer, GL::BufferDataUsage::StreamDraw, sizeof(Data)),
	Pos(0, sizeof(Data), indexPos),
	Col(0, sizeof(Data), indexCol)
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Col);
}

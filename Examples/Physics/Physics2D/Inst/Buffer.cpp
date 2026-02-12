#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL.hpp"



Physics2D::Main::Buffer::Buffer(
	unsigned int indexPos,
	unsigned int indexVel
) :
	::Buffer::Attribute(GL::BufferTarget::ArrayBuffer, GL::BufferDataUsage::StaticDraw, sizeof(Data)),
	Pos(1, sizeof(Data), indexPos),
	Vel(1, sizeof(Data), indexVel)
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Vel);
}

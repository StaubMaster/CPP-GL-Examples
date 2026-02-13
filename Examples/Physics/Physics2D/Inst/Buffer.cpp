#include "Buffer.hpp"
#include "Data.hpp"

#include "OpenGL.hpp"



Physics2D::Inst::Buffer::Buffer(
		unsigned int indexNowPos,
		unsigned int indexNowRot,
		unsigned int indexVelPos,
		unsigned int indexVelRot
)	: ::Buffer::Attribute(GL::BufferTarget::ArrayBuffer, GL::BufferDataUsage::StreamDraw, sizeof(Data))
	, Now(1, sizeof(Data), indexNowPos, indexNowRot)
	, Vel(1, sizeof(Data), indexVelPos, indexVelRot)
{
	Attributes.Allocate(2);
	Attributes.Insert(&Now);
	Attributes.Insert(&Vel);
}

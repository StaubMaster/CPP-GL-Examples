#include "Inst/Physics2D/Buffer.hpp"
#include "Inst/Physics2D/Data.hpp"

#include "OpenGL.hpp"



Physics2D::Inst::Buffer::Buffer(
	BufferArray::Base & buffer_array,
	unsigned int indexNowPos,
	unsigned int indexNowRot,
	unsigned int indexVelPos,
	unsigned int indexVelRot
)	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StreamDraw, 1, sizeof(Data))
	, Now(*this, indexNowPos, indexNowRot)
	, Vel(*this, indexVelPos, indexVelRot)
{
	Attributes.Allocate(2);
	Attributes.Insert(&Now);
	Attributes.Insert(&Vel);
}

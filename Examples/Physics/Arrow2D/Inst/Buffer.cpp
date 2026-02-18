#include "Arrow2D/Inst/Buffer.hpp"
#include "Arrow2D/Inst/Data.hpp"

#include "OpenGL.hpp"



Arrow2D::Inst::Buffer::Buffer(
	unsigned int indexPos0,
	unsigned int indexPos1,
	unsigned int indexSize
)	: ::Buffer::Attribute(GL::BufferTarget::ArrayBuffer, GL::BufferDataUsage::StaticDraw, sizeof(Data))
	, Pos0(1, sizeof(Data), indexPos0)
	, Pos1(1, sizeof(Data), indexPos1)
	, Size(1, sizeof(Data), indexSize)
{
	Attributes.Allocate(3);
	Attributes.Insert(&Pos0);
	Attributes.Insert(&Pos1);
	Attributes.Insert(&Size);
}

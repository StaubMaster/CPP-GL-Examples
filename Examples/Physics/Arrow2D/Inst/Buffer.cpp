#include "Arrow2D/Inst/Buffer.hpp"
#include "Arrow2D/Inst/Data.hpp"

#include "OpenGL.hpp"



Arrow2D::Inst::Buffer::Buffer(
	unsigned int indexPos0,
	unsigned int indexPos1,
	unsigned int indexSize,
	unsigned int indexCol
)	: ::Buffer::Attribute(GL::BufferTarget::ArrayBuffer, GL::BufferDataUsage::StaticDraw, sizeof(Data))
	, Pos0(1, sizeof(Data), indexPos0)
	, Pos1(1, sizeof(Data), indexPos1)
	, Size(1, sizeof(Data), indexSize)
	, Col(1, sizeof(Data), indexCol)
{
	Attributes.Allocate(4, 0);
	Attributes.Insert(&Pos0);
	Attributes.Insert(&Pos1);
	Attributes.Insert(&Size);
	Attributes.Insert(&Col);
}

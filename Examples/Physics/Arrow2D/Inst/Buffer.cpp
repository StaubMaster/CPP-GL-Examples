#include "Arrow2D/Inst/Buffer.hpp"
#include "Arrow2D/Inst/Data.hpp"

#include "OpenGL.hpp"



Arrow2D::Inst::Buffer::Buffer(
	BufferArray::Base & buffer_array,
	unsigned int indexPos0,
	unsigned int indexPos1,
	unsigned int indexSize,
	unsigned int indexCol
)	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 1, sizeof(Data))
	, Pos0(*this, indexPos0)
	, Pos1(*this, indexPos1)
	, Size(*this, indexSize)
	, Col(*this, indexCol)
{
	Attributes.Allocate(4, 0);
	Attributes.Insert(&Pos0);
	Attributes.Insert(&Pos1);
	Attributes.Insert(&Size);
	Attributes.Insert(&Col);
}

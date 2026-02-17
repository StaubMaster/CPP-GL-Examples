#include "Arrow2D/Inst/Buffer.hpp"
#include "Arrow2D/Inst/Data.hpp"

#include "OpenGL.hpp"



Arrow2D::Inst::Buffer::Buffer(
	unsigned int indexPos,
	unsigned int indexDir,
	unsigned int indexSize
)	: ::Buffer::Attribute(GL::BufferTarget::ArrayBuffer, GL::BufferDataUsage::StaticDraw, sizeof(Data))
	, Pos(1, sizeof(Data), indexPos)
	, Dir(1, sizeof(Data), indexDir)
	, Size(1, sizeof(Data), indexSize)
{
	Attributes.Allocate(3);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Dir);
	Attributes.Insert(&Size);
}

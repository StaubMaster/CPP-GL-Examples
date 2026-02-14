#include "PolyGon/Main/Buffer.hpp"
#include "PolyGon/Main/Data.hpp"

#include "OpenGL.hpp"



Physics2D::Main::Buffer::Buffer(
	unsigned int indexPos,
	unsigned int indexCol
)	: ::Buffer::Attribute(GL::BufferTarget::ArrayBuffer, GL::BufferDataUsage::StaticDraw, sizeof(Data))
	, Pos(0, sizeof(Data), indexPos)
	, Col(0, sizeof(Data), indexCol)
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Col);
}

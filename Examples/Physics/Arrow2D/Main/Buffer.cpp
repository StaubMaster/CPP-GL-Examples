#include "Arrow2D/Main/Buffer.hpp"
#include "Arrow2D/Main/Data.hpp"

#include "OpenGL.hpp"



Arrow2D::Main::Buffer::Buffer(
	unsigned int indexPos,
	unsigned int indexTex
)	: ::Buffer::Attribute(GL::BufferTarget::ArrayBuffer, GL::BufferDataUsage::StaticDraw, sizeof(Data))
	, Pos(0, sizeof(Data), indexPos)
	, Tex(0, sizeof(Data), indexTex)
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Tex);
}

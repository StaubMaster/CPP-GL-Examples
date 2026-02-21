#include "Arrow2D/Main/Buffer.hpp"
#include "Arrow2D/Main/Data.hpp"

#include "OpenGL.hpp"



Arrow2D::Main::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(Data))
	, Pos()
	, Tex()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Tex);
}

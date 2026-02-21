#include "PolyGon/Main/Buffer.hpp"
#include "PolyGon/Main/Data.hpp"

#include "OpenGL.hpp"



Physics2D::Main::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(Data))
	, Pos()
	, Col()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Col);
}

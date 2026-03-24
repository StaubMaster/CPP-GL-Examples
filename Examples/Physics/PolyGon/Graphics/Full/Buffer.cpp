#include "PolyGon/Graphics/Full/Buffer.hpp"
#include "PolyGon/Graphics/Full/Data.hpp"

#include "OpenGL.hpp"



PolyGon::Full::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(Data))
	, Pos()
	, Col()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Col);
}

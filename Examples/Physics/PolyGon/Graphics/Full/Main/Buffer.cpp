#include "PolyGon/Graphics/Full/Main/Buffer.hpp"
#include "PolyGon/Graphics/Full/Main/Data.hpp"

#include "OpenGLTypes.hpp"



PolyGonFull::Main::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(Data))
	, Pos()
	, Col()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Col);
}

#include "Grid2D/Graphics/Main/Buffer.hpp"
#include "Grid2D/Graphics/Main/Data.hpp"
#include "OpenGLTypes.hpp"



Grid2DGraphics::Main::Buffer::~Buffer() { }
Grid2DGraphics::Main::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(Main::Data))
	, Pos()
{
	Attributes.Allocate(1);
	Attributes.Insert(&Pos);
}

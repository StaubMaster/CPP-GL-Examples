#include "PolyGon/Graphics/Wire/Main/Buffer.hpp"
#include "PolyGon/Object.hpp"
#include "OpenGL.hpp"



PolyGon::Wire::Main::Buffer::~Buffer() { }
PolyGon::Wire::Main::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(PolyGon::Object::Corner))
	, Pos()
	, Col()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Pos);
	Attributes.Insert(&Col);
}



PolyGon::Wire::Elem::Buffer::~Buffer() { }
PolyGon::Wire::Elem::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Element(buffer_array, GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt)
{ }

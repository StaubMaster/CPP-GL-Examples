#include "Graphics/Buffer/Element.hpp"
#include "OpenGL.hpp"

//#include "OpenGL/Errors.hpp"
#include "Debug.hpp"
#include <sstream>
//#include <iostream>



void Buffer::Element::LogInfo(bool self) const
{
	(void)self;
	Debug::Log << Debug::Tabs << "Buffer::Element\n";
	Debug::Log << Debug::TabInc;
	Debug::Log << Debug::Tabs << "Usade: " << Usage << '\n';
	Debug::Log << Debug::Tabs << "IndexType: " << IndexType << '\n';
	Debug::Log << Debug::TabDec;
}

Buffer::Element::~Element() { }
Buffer::Element::Element(::BufferArray::Base & buffer_array, GL::BufferDataUsage usage, GL::DrawIndexType index_type, unsigned int elem_per_type)
	: Buffer::Base(buffer_array, GL::BufferTarget::ElementArrayBuffer)
	, Usage(usage)
	, IndexType(index_type)
	, ElemPerType(elem_per_type)
	, DrawCount(0)
{ }

Buffer::Element::Element(const Element & other)
	: Buffer::Base(other)
	, Usage(other.Usage)
	, IndexType(other.IndexType)
	, ElemPerType(other.ElemPerType)
	, DrawCount(other.DrawCount)
{ }
Buffer::Element & Buffer::Element::operator=(const Element & other)
{
	Base::operator=(other);
	Usage = other.Usage;
	IndexType = other.IndexType;
	ElemPerType = other.ElemPerType;
	DrawCount = other.DrawCount;
	return *this;
}

void Buffer::Element::Init() { }

void Buffer::Element::Change(const Container::Void & data)
{
	Bind();
	GL::BufferData(Target, data.VoidCount(), data.VoidData(), Usage);

	DrawCount = data.Count() * ElemPerType;
}

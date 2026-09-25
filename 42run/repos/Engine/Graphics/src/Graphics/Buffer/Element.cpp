#include "Graphics/Buffer/Element.hpp"
#include "OpenGLEnums.hpp"



Buffer::Element::~Element()
{ }
Buffer::Element::Element(GL::BufferDataUsage usage, GL::DrawIndexType index_type)
	: Buffer::Base(GL::BufferTarget::ElementArrayBuffer, usage)
	, IndexType(index_type)
{ }

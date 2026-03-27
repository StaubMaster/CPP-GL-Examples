#include "PolyGon/Graphics/Wire/Elem/Buffer.hpp"
#include "PolyGon/PolyGon.hpp"
#include "OpenGL.hpp"



PolyGonWire::Elem::Buffer::~Buffer() { }
PolyGonWire::Elem::Buffer::Buffer(BufferArray::Base & buffer_array, unsigned int elem_per_type)
	: ::Buffer::Element(buffer_array, GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt, elem_per_type)
{ }

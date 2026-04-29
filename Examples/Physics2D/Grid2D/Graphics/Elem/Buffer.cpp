#include "Grid2D/Graphics/Elem/Buffer.hpp"
#include "Grid2D/Graphics/Elem/Data.hpp"
#include "OpenGLTypes.hpp"



Grid2DGraphics::Elem::Buffer::~Buffer() { }
Grid2DGraphics::Elem::Buffer::Buffer(VertexArray & vertex_array, unsigned int elem_per_type)
	: ::Buffer::Element(buffer_array, GL::BufferDataUsage::StaticDraw, GL::DrawIndexType::UnsignedInt, elem_per_type)
{ }

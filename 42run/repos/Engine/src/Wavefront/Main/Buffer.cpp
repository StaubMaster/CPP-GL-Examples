#include "Wavefront/Main/Buffer.hpp"
#include "Wavefront/Main/Data.hpp"
#include "OpenGL.hpp"


Wavefront::Main::Buffer::~Buffer() { }

Wavefront::Main::Buffer::Buffer(VertexArray & vertex_array)
	: ::Buffer::Array(buffer_array, GL::BufferDataUsage::StaticDraw, 0, sizeof(Main::Data))
	, Position()
	, Texture()
	, Normal()
	, Color()
	, AmbientColor()
	, DiffuseColor()
	, SpecularPower()
	, SpecularColor()
{
	Attributes.Allocate(8);
	Attributes.Insert(&Position);
	Attributes.Insert(&Texture);
	Attributes.Insert(&Normal);
	Attributes.Insert(&Color);
	Attributes.Insert(&AmbientColor);
	Attributes.Insert(&DiffuseColor);
	Attributes.Insert(&SpecularPower);
	Attributes.Insert(&SpecularColor);
}

#include "Instance/Basic3D/Buffer.hpp"
#include "Instance/Basic3D/Data.hpp"

#include "OpenGLTypes.hpp"



Instance::Basic3D::Buffer::~Buffer() { }

Instance::Basic3D::Buffer::Buffer(BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StreamDraw, 1, sizeof(Data))
	, Trans()
	, Normal()
{
	Attributes.Allocate(2);
	Attributes.Insert(&Trans);
	Attributes.Insert(&Normal);
}

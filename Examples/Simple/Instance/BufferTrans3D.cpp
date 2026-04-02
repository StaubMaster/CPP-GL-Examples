#include "Instance/BufferTrans3D.hpp"
#include "ValueType/Trans3D.hpp"
#include "ValueType/Matrix4x4.hpp"

#include "OpenGL.hpp"



Instance::BufferTrans3D::BufferTrans3D(BufferArray::Base & buffer_array)
	: ::Buffer::Attribute(buffer_array, GL::BufferDataUsage::StreamDraw, 1, sizeof(Matrix4x4))
	, Data()
{
	Attributes.Allocate(1);
	Attributes.Insert(&Data);
}

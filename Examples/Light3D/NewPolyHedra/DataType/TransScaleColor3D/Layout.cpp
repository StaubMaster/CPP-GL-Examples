#include "Layout.hpp"
#include "InstanceData.hpp"



TransScaleColor3D::BufferLayout::~BufferLayout()
{ }
TransScaleColor3D::BufferLayout::BufferLayout()
	: ::Attribute::Layout(1, sizeof(InstanceData))
	, Trans(*this)
	, Normal(*this)
	, Scale(*this)
	, Color(*this)
{ }

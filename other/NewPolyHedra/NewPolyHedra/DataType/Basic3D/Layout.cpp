#include "Layout.hpp"
#include "InstanceData.hpp"



NewPolyHedra::Basic3D::BufferLayout::~BufferLayout()
{ }
NewPolyHedra::Basic3D::BufferLayout::BufferLayout()
	: ::Attribute::Layout(1, sizeof(NewPolyHedra::Basic3D::InstanceData))
	, Trans(*this)
	, Normal(*this)
{ }

#include "Layout.hpp"
#include "Display/Data.hpp"



TransScaleColor3D::BufferLayout::BufferLayout()
	: ::Attribute::Layout(1, sizeof(DisplayData))
	, Trans(*this)
	, Color(*this)
{ }

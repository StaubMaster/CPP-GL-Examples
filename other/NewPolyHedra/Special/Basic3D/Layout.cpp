#include "Layout.hpp"
#include "Display/Data.hpp"



NewPolyHedra::Basic3D::BufferLayout::BufferLayout()
	: ::Attribute::Layout(1, sizeof(DisplayData))
	, Trans(*this)
	, Normal(*this)
{ }

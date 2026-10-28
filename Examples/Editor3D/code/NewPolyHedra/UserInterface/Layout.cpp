#include "NewPolyHedra/UserInterface/Layout.hpp"
#include "NewPolyHedra/UserInterface/Display/Data.hpp"



NewPolyHedra::UserInterface::BufferLayout::BufferLayout()
	: ::Attribute::Layout(1, sizeof(DisplayData))
	, Size(*this)
	, Pos(*this)
	, Rot(*this)
	, Scale(*this)
{ }

#include "Layout/Multiform.hpp"



MultiformLayout::~MultiformLayout()
{ }
MultiformLayout::MultiformLayout()
	: Multiform::Layout()
	, DisplaySize("DisplaySize")
	, View("View")
	, Depth("Depth")
	, FOV("FOV")
{
	Multiforms.Insert(&DisplaySize);
	Multiforms.Insert(&View);
	Multiforms.Insert(&Depth);
	Multiforms.Insert(&FOV);
}

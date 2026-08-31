#include "MultiformLayouts.hpp"



MultiformLayoutDisplay::~MultiformLayoutDisplay()
{ }
MultiformLayoutDisplay::MultiformLayoutDisplay()
	: ::Multiform::Layout()
	, DisplaySize("DisplaySize")
{
	Multiforms.Insert(&DisplaySize);
}



MultiformLayoutView3D::~MultiformLayoutView3D()
{ }
MultiformLayoutView3D::MultiformLayoutView3D()
	: MultiformLayoutDisplay()
	, View("View")
	, Depth("Depth")
	, FOV("FOV")
{
	Multiforms.Insert(&View);
	Multiforms.Insert(&Depth);
	Multiforms.Insert(&FOV);
}

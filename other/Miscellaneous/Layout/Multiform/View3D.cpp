#include "Layout/Multiform/View3D.hpp"



LayoutMultiformView3D::LayoutMultiformView3D()
	: LayoutMultiformDisplay()
	, View("View")
	, Depth("Depth")
	, FOV("FOV")
{
	Multiforms.Insert(&View);
	Multiforms.Insert(&Depth);
	Multiforms.Insert(&FOV);
}

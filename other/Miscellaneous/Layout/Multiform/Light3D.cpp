#include "Layout/Multiform/Light3D.hpp"



LayoutMultiformLight3D::LayoutMultiformLight3D()
	: LayoutMultiformView3D()
	, Lights("ILights")
{
	Multiforms.Insert(&Lights);
}

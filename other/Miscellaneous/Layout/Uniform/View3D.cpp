#include "Layout/Uniform/View3D.hpp"



LayoutUniformView3D::LayoutUniformView3D()
	: LayoutUniformDisplay()
	, View(*this, "View")
	, Depth(*this, "Depth")
	, FOV(*this, "FOV")
{ }

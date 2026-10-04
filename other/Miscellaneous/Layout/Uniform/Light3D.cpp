#include "Layout/Uniform/Light3D.hpp"



LayoutUniformLight3D::LayoutUniformLight3D()
	: LayoutUniformView3D()
	, Lights(*this, "ILights")
{ }

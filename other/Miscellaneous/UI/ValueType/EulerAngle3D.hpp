#ifndef  PROPERTY_CONTROL_EULER_ANGLE_3D_HPP
# define PROPERTY_CONTROL_EULER_ANGLE_3D_HPP

# include "UI/NestedProperty.hpp"
# include "Control/Controls/Label.hpp"

struct EulerAngle3D;

namespace UI
{
struct EulerAngle3D : public NestedProperty
{
	UI::Control_::Label	Z0;
	UI::Control_::Label	X1;
	UI::Control_::Label	Y2;

	EulerAngle3D(const char * name);

	::EulerAngle3D * Object;
	void	Syncronize();
	void	Change(::EulerAngle3D * obj);
};
};

#endif
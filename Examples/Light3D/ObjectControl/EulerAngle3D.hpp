#ifndef  OBJECT_CONTROL_EULER_ANGLE_3D_HPP
# define OBJECT_CONTROL_EULER_ANGLE_3D_HPP

# include "Control/GroupBox.hpp"
# include "Control/Label.hpp"

struct EulerAngle3D;

namespace UI
{
namespace Control
{
struct EulerAngle3D : public GroupBox
{
	Label	Z0;
	Label	X1;
	Label	Y2;

	~EulerAngle3D();
	EulerAngle3D();

	::EulerAngle3D * Object;
	void	Change(::EulerAngle3D * obj);
};
};
};

#endif
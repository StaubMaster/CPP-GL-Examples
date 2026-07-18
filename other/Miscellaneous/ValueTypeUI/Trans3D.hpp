#ifndef  PROPERTY_CONTROL_TRANS_3D_HPP
# define PROPERTY_CONTROL_TRANS_3D_HPP

# include "ValueTypeUI/PropertyControl.hpp"
# include "ValueTypeUI/VectorF3.hpp"
# include "ValueTypeUI/EulerAngle3D.hpp"

struct Trans3D;

namespace UI
{
namespace Control
{
struct Trans3D : public PropertyControl
{
	VectorF3		Position;
	EulerAngle3D	Rotation;

	~Trans3D();
	Trans3D(const char * name);

	::Trans3D *	Object;
	void	Update();
	void	Change(::Trans3D * obj);

};
};
};

#endif
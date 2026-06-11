#ifndef  PROPERTY_CONTROL_TRANS_3D_HPP
# define PROPERTY_CONTROL_TRANS_3D_HPP

# include "PropertyControl.hpp"
# include "PropertyControl/VectorF3.hpp"
# include "PropertyControl/EulerAngle3D.hpp"

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
	void	Change(::Trans3D * obj);

};
};
};

#endif
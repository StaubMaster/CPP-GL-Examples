#ifndef  PROPERTY_CONTROL_TRANS_3D_HPP
# define PROPERTY_CONTROL_TRANS_3D_HPP

# include "UI/NestedProperty.hpp"
# include "UI/ValueType/VectorF3.hpp"
# include "UI/ValueType/EulerAngle3D.hpp"

struct Trans3D;

namespace UI
{
struct Trans3D : public NestedProperty
{
	VectorF3		Position;
	EulerAngle3D	Rotation;

	Trans3D(const char * name);

	::Trans3D *	Object;
	void	Syncronize();
	void	Change(::Trans3D * obj);
};
};

#endif
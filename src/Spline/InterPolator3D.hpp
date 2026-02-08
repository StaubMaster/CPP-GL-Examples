#ifndef  INTERPOLATOR_3D_HPP
# define INTERPOLATOR_3D_HPP

# include "DataDeclare.hpp"

class InterPolator3D
{
	public:
	~InterPolator3D();
	InterPolator3D();
	InterPolator3D(const InterPolator3D & other);
	InterPolator3D & operator=(const InterPolator3D & other);

	public:
	virtual Point3D InterPolate(float t) = 0;
};

#endif
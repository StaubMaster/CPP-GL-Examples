#ifndef  INTERPOLATOR_3D_HPP
# define INTERPOLATOR_3D_HPP

# include "ValueType/_Declare.hpp"

class InterPolator3D
{
	public:
	virtual ~InterPolator3D();
	InterPolator3D();
	InterPolator3D(const InterPolator3D & other);
	InterPolator3D & operator=(const InterPolator3D & other);

	public:
	virtual VectorF3 InterPolatePos(float t) = 0;
	virtual VectorF3 InterPolateDir(float t) = 0;
};

#endif
#ifndef  LINEAR_3D_HPP
# define LINEAR_3D_HPP

# include "Interpolator3D.hpp"
# include "ValueType/Point3D.hpp"

class Linear3D : public InterPolator3D
{
	public:
	Point3D	Pole0;
	Point3D	Pole1;

	public:
	~Linear3D();
	Linear3D();
	Linear3D(const Linear3D & other);
	Linear3D & operator=(const Linear3D & other);

	public:
	Point3D InterPolate(float t) override;
};

#endif
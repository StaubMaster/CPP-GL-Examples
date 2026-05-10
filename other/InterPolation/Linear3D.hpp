#ifndef  LINEAR_3D_HPP
# define LINEAR_3D_HPP

# include "Interpolator3D.hpp"
# include "ValueType/VectorF3.hpp"

class Linear3D : public InterPolator3D
{
	public:
	VectorF3	Pole0;
	VectorF3	Pole1;

	public:
	~Linear3D();
	Linear3D();
	Linear3D(const Linear3D & other);
	Linear3D & operator=(const Linear3D & other);

	public:
	VectorF3 InterPolate(float t) override;
};

#endif
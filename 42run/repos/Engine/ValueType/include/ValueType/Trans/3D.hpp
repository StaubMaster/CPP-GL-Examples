#ifndef  TRANS_3D_HPP
# define TRANS_3D_HPP

# include "ValueType/Vector/F3.hpp"
# include "ValueType/EulerAngle3D.hpp"

struct Trans3D
{
	VectorF3		Position;
	EulerAngle3D	Rotation;
	// Scale
	// Shear
	// Distort
	/*
		there are different combinations of how to Transform
		this is "regular"
	*/

	~Trans3D() = default;
	Trans3D() = default;
	Trans3D(const Trans3D & other) = default;
	Trans3D & operator=(const Trans3D & other) = default;

	Trans3D(const VectorF3 & pos);
	Trans3D(const EulerAngle3D & rot);
	Trans3D(const VectorF3 & pos, const EulerAngle3D & rot);



	VectorF3	forward(const VectorF3 & vec) const;
	VectorF3	reverse(const VectorF3 & vec) const;

	Trans3D		forward(const Trans3D & other) const;
};


#endif
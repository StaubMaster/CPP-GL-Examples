#ifndef  EULER_ANGLE_3D_HPP
# define EULER_ANGLE_3D_HPP

# include "Angle.hpp"

struct VectorF3;

struct EulerAngle3D
{
	public:
	Angle	Z0;
	Angle	X1;
	Angle	Y2;



	public:
	~EulerAngle3D() = default;
	EulerAngle3D() = default;
	EulerAngle3D(const EulerAngle3D & other) = default;
	EulerAngle3D & operator=(const EulerAngle3D & other) = default;



	public:
	EulerAngle3D(Angle z0, Angle x1, Angle y2);

	static EulerAngle3D		Degrees(float z0, float x1, float y2);
	static EulerAngle3D		Radians(float z0, float x1, float y2);

	static EulerAngle3D		PointToX(VectorF3 dir);
	static EulerAngle3D		PointToY(VectorF3 dir);
	static EulerAngle3D		PointToZ(VectorF3 dir);



	public:
	EulerAngle3D	round(Angle size) const;
	EulerAngle3D	roundC(Angle size) const;
	EulerAngle3D	roundF(Angle size) const;



	public:

	VectorF3		forward(VectorF3 p) const;
	VectorF3		reverse(VectorF3 p) const;

	EulerAngle3D	forward(const EulerAngle3D & other) const;
	EulerAngle3D	reverse(const EulerAngle3D & other) const;

	EulerAngle3D	reverse() const;



	public:

	EulerAngle3D	operator+() const;
	EulerAngle3D	operator-() const;

	EulerAngle3D	operator+(const EulerAngle3D & other) const;
	EulerAngle3D	operator-(const EulerAngle3D & other) const;

	EulerAngle3D &	operator+=(const EulerAngle3D & other);
	EulerAngle3D &	operator-=(const EulerAngle3D & other);

	EulerAngle3D	operator*(const float & flt) const;
	EulerAngle3D	operator/(const float & flt) const;

	EulerAngle3D &	operator*=(const float & flt);
	EulerAngle3D &	operator/=(const float & flt);
};

#endif

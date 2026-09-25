#ifndef  VECTOR_F_4_HPP
# define VECTOR_F_4_HPP

struct Bool4;

struct VectorF4
{
	float	X = 0.0f;
	float	Y = 0.0f;
	float	Z = 0.0f;
	float	W = 0.0f;

	~VectorF4() = default;
	VectorF4() = default;
	VectorF4(const VectorF4 & other) = default;
	VectorF4 & operator=(const VectorF4 & other) = default;

	VectorF4(float x, float y, float z, float w);
	VectorF4(float value);

//	VectorI4	ToI() const;
//	VectorU4	ToU() const;



	VectorF4	Min(const VectorF4 & other) const;
	VectorF4	Max(const VectorF4 & other) const;
	VectorF4	Mix(const VectorF4 & other, const Bool4 & condition) const;

	static VectorF4		Min(const VectorF4 & vec0, const VectorF4 & vec1);
	static VectorF4		Max(const VectorF4 & vec0, const VectorF4 & vec1);
	static VectorF4		Mix(const VectorF4 & vec0, const VectorF4 & vec1, const Bool4 & condition);



	float		length2() const;
	float		length() const;

	VectorF4		normalize() const;
	VectorF4		normalize(float & len) const;
	VectorF4		operator!() const;

	VectorF4		round() const;
	VectorF4		roundC() const;
	VectorF4		roundF() const;

	VectorF4		round(float size) const;
	VectorF4		roundC(float size) const;
	VectorF4		roundF(float size) const;

	VectorF4		abs() const;



			float	dot(const VectorF4 & other) const;
	static	float	dot(const VectorF4 & v0, const VectorF4 & v1);



	Bool4			operator==(const VectorF4 & other) const;
	Bool4			operator!=(const VectorF4 & other) const;
	Bool4			operator< (const VectorF4 & other) const;
	Bool4			operator> (const VectorF4 & other) const;
	Bool4			operator<=(const VectorF4 & other) const;
	Bool4			operator>=(const VectorF4 & other) const;

	VectorF4		operator+() const;
	VectorF4		operator-() const;

	VectorF4		operator+(const VectorF4 & other) const;
	VectorF4		operator-(const VectorF4 & other) const;
	VectorF4		operator*(const VectorF4 & other) const;
	VectorF4		operator/(const VectorF4 & other) const;

	VectorF4 &		operator+=(const VectorF4 & other);
	VectorF4 &		operator-=(const VectorF4 & other);
	VectorF4 &		operator*=(const VectorF4 & other);
	VectorF4 &		operator/=(const VectorF4 & other);

	VectorF4 &		operator+=(const float & val);
	VectorF4 &		operator-=(const float & val);
	VectorF4 &		operator*=(const float & val);
	VectorF4 &		operator/=(const float & val);
};

VectorF4		operator+(const VectorF4 & vec, const float & val);
VectorF4		operator-(const VectorF4 & vec, const float & val);
VectorF4		operator*(const VectorF4 & vec, const float & val);
VectorF4		operator/(const VectorF4 & vec, const float & val);

VectorF4		operator+(const float & val, const VectorF4 & vec);
VectorF4		operator-(const float & val, const VectorF4 & vec);
VectorF4		operator*(const float & val, const VectorF4 & vec);
VectorF4		operator/(const float & val, const VectorF4 & vec);

#endif
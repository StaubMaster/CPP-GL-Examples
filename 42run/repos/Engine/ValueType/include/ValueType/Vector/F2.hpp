#ifndef  VECTOR_F_2_HPP
# define VECTOR_F_2_HPP

struct Bool2;
struct VectorI2;
struct VectorU2;

struct VectorF2
{
	float	X = 0.0f;
	float	Y = 0.0f;

	~VectorF2() = default;
	VectorF2() = default;
	VectorF2(const VectorF2 & other) = default;
	VectorF2 & operator=(const VectorF2 & other) = default;

	VectorF2(float x, float y);
	VectorF2(float value);

	VectorI2	ToI() const;
	VectorU2	ToU() const;



	VectorF2	Min(const VectorF2 & other) const;
	VectorF2	Max(const VectorF2 & other) const;
	VectorF2	Mix(const VectorF2 & other, const Bool2 & condition) const;

	static VectorF2		Min(const VectorF2 & vec0, const VectorF2 & vec1);
	static VectorF2		Max(const VectorF2 & vec0, const VectorF2 & vec1);
	static VectorF2		Mix(const VectorF2 & vec0, const VectorF2 & vec1, const Bool2 & condition);




	float		length2() const;
	float		length() const;

	VectorF2		normalize() const;
	VectorF2		normalize(float & len) const;
	VectorF2		operator!() const;

	VectorF2		round() const;
	VectorF2		roundC() const;
	VectorF2		roundF() const;

	VectorF2		round(float size) const;
	VectorF2		roundC(float size) const;
	VectorF2		roundF(float size) const;

	VectorF2		abs() const;



			float	dot(const VectorF2 & other) const;
	static	float	dot(const VectorF2 & v0, const VectorF2 & v1);



			float	cross(const VectorF2 & other) const;
	static	float	cross(const VectorF2 & vec0, const VectorF2 & vec1);

			VectorF2	cross(float f) const;
	static	VectorF2	cross(float f, const VectorF2 & v);
	static	VectorF2	cross(const VectorF2 & v, float f);



	Bool2			operator==(const VectorF2 & other) const;
	Bool2			operator!=(const VectorF2 & other) const;
	Bool2			operator< (const VectorF2 & other) const;
	Bool2			operator> (const VectorF2 & other) const;
	Bool2			operator<=(const VectorF2 & other) const;
	Bool2			operator>=(const VectorF2 & other) const;

	VectorF2		operator+() const;
	VectorF2		operator-() const;

	VectorF2		operator+(const VectorF2 & other) const;
	VectorF2		operator-(const VectorF2 & other) const;
	VectorF2		operator*(const VectorF2 & other) const;
	VectorF2		operator/(const VectorF2 & other) const;

	VectorF2 &		operator+=(const VectorF2 & other);
	VectorF2 &		operator-=(const VectorF2 & other);
	VectorF2 &		operator*=(const VectorF2 & other);
	VectorF2 &		operator/=(const VectorF2 & other);

	VectorF2 &		operator+=(const float & val);
	VectorF2 &		operator-=(const float & val);
	VectorF2 &		operator*=(const float & val);
	VectorF2 &		operator/=(const float & val);
};

VectorF2		operator+(const VectorF2 & vec, const float & val);
VectorF2		operator-(const VectorF2 & vec, const float & val);
VectorF2		operator*(const VectorF2 & vec, const float & val);
VectorF2		operator/(const VectorF2 & vec, const float & val);

VectorF2		operator+(const float & val, const VectorF2 & vec);
VectorF2		operator-(const float & val, const VectorF2 & vec);
VectorF2		operator*(const float & val, const VectorF2 & vec);
VectorF2		operator/(const float & val, const VectorF2 & vec);

#endif
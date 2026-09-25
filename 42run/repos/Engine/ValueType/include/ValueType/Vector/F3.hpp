#ifndef  VECTOR_F_3_HPP
# define VECTOR_F_3_HPP

struct Bool3;
struct VectorI3;
struct VectorU3;

struct VectorF3
{
	float	X = 0.0f;
	float	Y = 0.0f;
	float	Z = 0.0f;

	~VectorF3() = default;
	VectorF3() = default;
	VectorF3(const VectorF3 & other) = default;
	VectorF3 & operator=(const VectorF3 & other) = default;

	VectorF3(float x, float y, float z);
	VectorF3(float value);

	VectorI3	ToI() const;
	VectorU3	ToU() const;



	VectorF3	Min(const VectorF3 & other) const;
	VectorF3	Max(const VectorF3 & other) const;
	VectorF3	Mix(const VectorF3 & other, const Bool3 & condition) const;

	static VectorF3		Min(const VectorF3 & vec0, const VectorF3 & vec1);
	static VectorF3		Max(const VectorF3 & vec0, const VectorF3 & vec1);
	static VectorF3		Mix(const VectorF3 & vec0, const VectorF3 & vec1, const Bool3 & condition);



	float		length2() const;
	float		length() const;

	VectorF3		normalize() const;
	VectorF3		normalize(float & len) const;
	VectorF3		operator!() const;

	VectorF3		round() const;
	VectorF3		roundC() const;
	VectorF3		roundF() const;

	VectorF3		round(float size) const;
	VectorF3		roundC(float size) const;
	VectorF3		roundF(float size) const;

	VectorF3		abs() const;



			float	dot(const VectorF3 & other) const;
	static	float	dot(const VectorF3 & v0, const VectorF3 & v1);



	static	VectorF3	cross(const VectorF3 & v0, const VectorF3 & v1);
			VectorF3	cross(const VectorF3 & other) const;



	/* RankDimensions()
		returns a VectorI3 with values n = [-1;D-1] (D=3)
		n == [0:2] means that Dimension is larger then n other Dimensions
		n == -1 means that that Dimension is NaN
		Dimension being the same is currently undefined bacause I dont feel like defining it
	*/
	VectorI3		RankDimensions() const;



	Bool3			operator==(const VectorF3 & other) const;
	Bool3			operator!=(const VectorF3 & other) const;
	Bool3			operator< (const VectorF3 & other) const;
	Bool3			operator> (const VectorF3 & other) const;
	Bool3			operator<=(const VectorF3 & other) const;
	Bool3			operator>=(const VectorF3 & other) const;

	VectorF3		operator+() const;
	VectorF3		operator-() const;

	VectorF3		operator+(const VectorF3 & other) const;
	VectorF3		operator-(const VectorF3 & other) const;
	VectorF3		operator*(const VectorF3 & other) const;
	VectorF3		operator/(const VectorF3 & other) const;

	VectorF3 &		operator+=(const VectorF3 & other);
	VectorF3 &		operator-=(const VectorF3 & other);
	VectorF3 &		operator*=(const VectorF3 & other);
	VectorF3 &		operator/=(const VectorF3 & other);

	VectorF3 &		operator+=(const float & val);
	VectorF3 &		operator-=(const float & val);
	VectorF3 &		operator*=(const float & val);
	VectorF3 &		operator/=(const float & val);
};

VectorF3		operator+(const VectorF3 & vec, const float & val);
VectorF3		operator-(const VectorF3 & vec, const float & val);
VectorF3		operator*(const VectorF3 & vec, const float & val);
VectorF3		operator/(const VectorF3 & vec, const float & val);

VectorF3		operator+(const float & val, const VectorF3 & vec);
VectorF3		operator-(const float & val, const VectorF3 & vec);
VectorF3		operator*(const float & val, const VectorF3 & vec);
VectorF3		operator/(const float & val, const VectorF3 & vec);

#endif
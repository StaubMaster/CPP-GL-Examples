#ifndef  VECTOR_F_3_HPP
# define VECTOR_F_3_HPP

# include "ValueType/Vector/_3.hpp"

struct VectorI3;

struct VectorF3 : public Vector_3<float, VectorF3>
{
	~VectorF3();

	VectorF3();
	VectorF3(float value);
	VectorF3(float x, float y, float z);

	VectorF3(const VectorF3 & other);
	VectorF3 & operator=(const VectorF3 & other);

	template<typename OtherVectorType> VectorF3(const OtherVectorType & other) : Vector_3(other) { }



	using	Vector_3::operator+;
	using	Vector_3::operator-;
	using	Vector_3::operator*;
	using	Vector_3::operator/;

	using	Vector_3::operator+=;
	using	Vector_3::operator-=;
	using	Vector_3::operator*=;
	using	Vector_3::operator/=;

	using	Vector_3::operator==;
	using	Vector_3::operator!=;
	using	Vector_3::operator<;
	using	Vector_3::operator>;
	using	Vector_3::operator<=;
	using	Vector_3::operator>=;



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
};

VectorF3		operator+(VectorF3 v, float f);
VectorF3		operator-(VectorF3 v, float f);
VectorF3		operator*(VectorF3 v, float f);
VectorF3		operator/(VectorF3 v, float f);

VectorF3		operator+(float f, VectorF3 v);
VectorF3		operator-(float f, VectorF3 v);
VectorF3		operator*(float f, VectorF3 v);
VectorF3		operator/(float f, VectorF3 v);

#endif
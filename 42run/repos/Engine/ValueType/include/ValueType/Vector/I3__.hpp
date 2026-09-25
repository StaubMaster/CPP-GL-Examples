#ifndef  VECTOR_I_3_HPP
# define VECTOR_I_3_HPP

# include "ValueType/Vector/_3.hpp"

struct VectorU3;
struct VectorF3;

struct VectorI3 : public Vector_3<int, VectorI3>
{
	~VectorI3() = default;
	VectorI3() = default;
	VectorI3(const VectorI3 & other) = default;
	VectorI3 & operator=(const VectorI3 & other) = default;

	VectorI3(int value);
	VectorI3(int x, int y, int z);

	VectorU3	ToU() const;
	VectorF3	ToF() const;



	int	Product() const;

	unsigned int	Convert(VectorI3 idx) const;
	VectorI3		Convert(unsigned int idx) const;

	static unsigned int		Convert(unsigned int size, VectorI3 idx);
	static VectorI3			Convert(unsigned int size, unsigned int idx);



	VectorI3	operator%(const VectorI3 & other) const;

	VectorI3	operator~() const;
	VectorI3	operator&(const VectorI3 & other) const;
	VectorI3	operator|(const VectorI3 & other) const;
	VectorI3	operator^(const VectorI3 & other) const;
	VectorI3	operator<<(const VectorI3 & other) const;
	VectorI3	operator>>(const VectorI3 & other) const;



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
};

//VectorI3	operator+(const VectorI3 & vec, const int & val);
//VectorI3	operator-(const VectorI3 & vec, const int & val);
//VectorI3	operator*(const VectorI3 & vec, const int & val);
//VectorI3	operator/(const VectorI3 & vec, const int & val);
//
//VectorI3	operator+(const int & val, const VectorI3 & vec);
//VectorI3	operator-(const int & val, const VectorI3 & vec);
//VectorI3	operator*(const int & val, const VectorI3 & vec);
//VectorI3	operator/(const int & val, const VectorI3 & vec);

#endif
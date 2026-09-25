#ifndef  VECTOR_U_3_HPP
# define VECTOR_U_3_HPP

# include "ValueType/Vector/_3.hpp"

struct VectorI3;
struct VectorF3;

struct VectorU3 : public Vector_3<unsigned int, VectorU3>
{
	~VectorU3() = default;
	VectorU3() = default;
	VectorU3(const VectorU3 & other) = default;
	VectorU3 & operator=(const VectorU3 & other) = default;

	VectorU3(unsigned int value);
	VectorU3(unsigned int x, unsigned int y, unsigned int z);

	VectorI3	ToI() const;
	VectorF3	ToF() const;



	unsigned int	Product() const;

	unsigned int	Convert(VectorU3 udx) const;
	VectorU3		Convert(unsigned int udx) const;

	static unsigned int		Convert(unsigned int size, VectorU3 udx);
	static VectorU3			Convert(unsigned int size, unsigned int udx);



	VectorU3	operator%(const VectorU3 & other) const;

	VectorU3	operator~() const;
	VectorU3	operator&(const VectorU3 & other) const;
	VectorU3	operator|(const VectorU3 & other) const;
	VectorU3	operator^(const VectorU3 & other) const;
	VectorU3	operator<<(const VectorU3 & other) const;
	VectorU3	operator>>(const VectorU3 & other) const;



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

VectorU3	operator+(const VectorU3 & vec, const unsigned int & val);
VectorU3	operator-(const VectorU3 & vec, const unsigned int & val);
VectorU3	operator*(const VectorU3 & vec, const unsigned int & val);
VectorU3	operator/(const VectorU3 & vec, const unsigned int & val);

VectorU3	operator+(const unsigned int & val, const VectorU3 & vec);
VectorU3	operator-(const unsigned int & val, const VectorU3 & vec);
VectorU3	operator*(const unsigned int & val, const VectorU3 & vec);
VectorU3	operator/(const unsigned int & val, const VectorU3 & vec);

#endif
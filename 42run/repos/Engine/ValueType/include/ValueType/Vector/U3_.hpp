#ifndef  VECTOR_U_3_HPP
# define VECTOR_U_3_HPP

# include "ValueType/Vector/_3.hpp"

struct VectorU3 : public Vector_3<unsigned int, VectorU3>
{
	~VectorU3();

	VectorU3();
	VectorU3(unsigned int value);
	VectorU3(unsigned int x, unsigned int y, unsigned int z);

	VectorU3(const VectorU3 & other);
	VectorU3 & operator=(const VectorU3 & other);

	template<typename OtherVectorType> VectorU3(const OtherVectorType & other) : Vector_3(other) { }



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



	VectorU3		operator%(const VectorU3 & other) const;

	VectorU3		operator~() const;
	VectorU3		operator&(const VectorU3 & other) const;
	VectorU3		operator|(const VectorU3 & other) const;
	VectorU3		operator^(const VectorU3 & other) const;
	VectorU3		operator<<(const VectorU3 & other) const;
	VectorU3		operator>>(const VectorU3 & other) const;



	unsigned int	Product() const;

	unsigned int	Convert(VectorU3 udx) const;
	VectorU3		Convert(unsigned int udx) const;

	static unsigned int		Convert(unsigned int size, VectorU3 udx);
	static VectorU3			Convert(unsigned int size, unsigned int udx);
};

VectorU3		operator+(VectorU3 vec, unsigned int val);
VectorU3		operator-(VectorU3 vec, unsigned int val);
VectorU3		operator*(VectorU3 vec, unsigned int val);
VectorU3		operator/(VectorU3 vec, unsigned int val);

VectorU3		operator+(unsigned int val, VectorU3 vec);
VectorU3		operator-(unsigned int val, VectorU3 vec);
VectorU3		operator*(unsigned int val, VectorU3 vec);
VectorU3		operator/(unsigned int val, VectorU3 vec);

#endif
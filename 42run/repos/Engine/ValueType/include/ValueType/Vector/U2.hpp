#ifndef  VECTOR_U_2_HPP
# define VECTOR_U_2_HPP

struct Bool2;
struct VectorI2;
struct VectorF2;

struct VectorU2
{
	unsigned int	X = 0;
	unsigned int	Y = 0;

	~VectorU2() = default;
	VectorU2() = default;
	VectorU2(const VectorU2 & other) = default;
	VectorU2 & operator=(const VectorU2 & other) = default;

	VectorU2(unsigned int x, unsigned int y);
	VectorU2(unsigned int value);

	VectorI2	ToI() const;
	VectorF2	ToF() const;



	VectorU2	Min(const VectorU2 & other) const;
	VectorU2	Max(const VectorU2 & other) const;
	VectorU2	Mix(const VectorU2 & other, const Bool2 & condition) const;

	static VectorU2		Min(const VectorU2 & vec0, const VectorU2 & vec1);
	static VectorU2		Max(const VectorU2 & vec0, const VectorU2 & vec1);
	static VectorU2		Mix(const VectorU2 & vec0, const VectorU2 & vec1, const Bool2 & condition);



	unsigned int	Product() const;

	unsigned int	Convert(VectorU2 udx) const;
	VectorU2		Convert(unsigned int udx) const;

	static unsigned int		Convert(unsigned int size, VectorU2 udx);
	static VectorU2			Convert(unsigned int size, unsigned int udx);



	Bool2			operator==(const VectorU2 & other) const;
	Bool2			operator!=(const VectorU2 & other) const;
	Bool2			operator< (const VectorU2 & other) const;
	Bool2			operator> (const VectorU2 & other) const;
	Bool2			operator<=(const VectorU2 & other) const;
	Bool2			operator>=(const VectorU2 & other) const;

	VectorU2		operator+() const;
	VectorU2		operator-() const;

	VectorU2		operator+(const VectorU2 & other) const;
	VectorU2		operator-(const VectorU2 & other) const;
	VectorU2		operator*(const VectorU2 & other) const;
	VectorU2		operator/(const VectorU2 & other) const;

	VectorU2		operator%(const VectorU2 & other) const;

	VectorU2		operator~() const;

	VectorU2		operator&(const VectorU2 & other) const;
	VectorU2		operator|(const VectorU2 & other) const;
	VectorU2		operator^(const VectorU2 & other) const;

	VectorU2		operator<<(const VectorU2 & other) const;
	VectorU2		operator>>(const VectorU2 & other) const;

	VectorU2 &		operator+=(const VectorU2 & other);
	VectorU2 &		operator-=(const VectorU2 & other);
	VectorU2 &		operator*=(const VectorU2 & other);
	VectorU2 &		operator/=(const VectorU2 & other);

	VectorU2 &		operator+=(const unsigned int & val);
	VectorU2 &		operator-=(const unsigned int & val);
	VectorU2 &		operator*=(const unsigned int & val);
	VectorU2 &		operator/=(const unsigned int & val);
};

VectorU2		operator+(const VectorU2 & vec, const unsigned int & val);
VectorU2		operator-(const VectorU2 & vec, const unsigned int & val);
VectorU2		operator*(const VectorU2 & vec, const unsigned int & val);
VectorU2		operator/(const VectorU2 & vec, const unsigned int & val);

VectorU2		operator+(const unsigned int & val, const VectorU2 & vec);
VectorU2		operator-(const unsigned int & val, const VectorU2 & vec);
VectorU2		operator*(const unsigned int & val, const VectorU2 & vec);
VectorU2		operator/(const unsigned int & val, const VectorU2 & vec);

#endif
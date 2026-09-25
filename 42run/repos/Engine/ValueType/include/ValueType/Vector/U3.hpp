#ifndef  VECTOR_U_3_HPP
# define VECTOR_U_3_HPP

struct Bool3;
struct VectorI3;
struct VectorF3;

struct VectorU3
{
	unsigned int	X = 0;
	unsigned int	Y = 0;
	unsigned int	Z = 0;

	~VectorU3() = default;
	VectorU3() = default;
	VectorU3(const VectorU3 & other) = default;
	VectorU3 & operator=(const VectorU3 & other) = default;

	VectorU3(unsigned int x, unsigned int y, unsigned int z);
	VectorU3(unsigned int value);

	VectorI3	ToI() const;
	VectorF3	ToF() const;



	VectorU3	Min(const VectorU3 & other) const;
	VectorU3	Max(const VectorU3 & other) const;
	VectorU3	Mix(const VectorU3 & other, const Bool3 & condition) const;

	static VectorU3		Min(const VectorU3 & vec0, const VectorU3 & vec1);
	static VectorU3		Max(const VectorU3 & vec0, const VectorU3 & vec1);
	static VectorU3		Mix(const VectorU3 & vec0, const VectorU3 & vec1, const Bool3 & condition);



	unsigned int	Product() const;

	unsigned int	Convert(VectorU3 udx) const;
	VectorU3		Convert(unsigned int udx) const;

	static unsigned int		Convert(unsigned int size, VectorU3 udx);
	static VectorU3			Convert(unsigned int size, unsigned int udx);



	Bool3			operator==(const VectorU3 & other) const;
	Bool3			operator!=(const VectorU3 & other) const;
	Bool3			operator< (const VectorU3 & other) const;
	Bool3			operator> (const VectorU3 & other) const;
	Bool3			operator<=(const VectorU3 & other) const;
	Bool3			operator>=(const VectorU3 & other) const;

	VectorU3		operator+() const;
	VectorU3		operator-() const;

	VectorU3		operator+(const VectorU3 & other) const;
	VectorU3		operator-(const VectorU3 & other) const;
	VectorU3		operator*(const VectorU3 & other) const;
	VectorU3		operator/(const VectorU3 & other) const;

	VectorU3		operator%(const VectorU3 & other) const;

	VectorU3		operator~() const;

	VectorU3		operator&(const VectorU3 & other) const;
	VectorU3		operator|(const VectorU3 & other) const;
	VectorU3		operator^(const VectorU3 & other) const;

	VectorU3		operator<<(const VectorU3 & other) const;
	VectorU3		operator>>(const VectorU3 & other) const;

	VectorU3 &		operator+=(const VectorU3 & other);
	VectorU3 &		operator-=(const VectorU3 & other);
	VectorU3 &		operator*=(const VectorU3 & other);
	VectorU3 &		operator/=(const VectorU3 & other);

	VectorU3 &		operator+=(const unsigned int & val);
	VectorU3 &		operator-=(const unsigned int & val);
	VectorU3 &		operator*=(const unsigned int & val);
	VectorU3 &		operator/=(const unsigned int & val);
};

VectorU3		operator+(const VectorU3 & vec, const unsigned int & val);
VectorU3		operator-(const VectorU3 & vec, const unsigned int & val);
VectorU3		operator*(const VectorU3 & vec, const unsigned int & val);
VectorU3		operator/(const VectorU3 & vec, const unsigned int & val);

VectorU3		operator+(const unsigned int & val, const VectorU3 & vec);
VectorU3		operator-(const unsigned int & val, const VectorU3 & vec);
VectorU3		operator*(const unsigned int & val, const VectorU3 & vec);
VectorU3		operator/(const unsigned int & val, const VectorU3 & vec);

#endif
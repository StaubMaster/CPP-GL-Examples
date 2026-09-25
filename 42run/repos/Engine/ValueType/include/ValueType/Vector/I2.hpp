#ifndef  VECTOR_I_2_HPP
# define VECTOR_I_2_HPP

struct Bool2;
struct VectorU2;
struct VectorF2;

struct VectorI2
{
	int	X = 0;
	int	Y = 0;

	~VectorI2() = default;
	VectorI2() = default;
	VectorI2(const VectorI2 & other) = default;
	VectorI2 & operator=(const VectorI2 & other) = default;

	VectorI2(int x, int y);
	VectorI2(int value);

	VectorU2	ToU() const;
	VectorF2	ToF() const;



	VectorI2	Min(const VectorI2 & other) const;
	VectorI2	Max(const VectorI2 & other) const;
	VectorI2	Mix(const VectorI2 & other, const Bool2 & condition) const;

	static VectorI2		Min(const VectorI2 & vec0, const VectorI2 & vec1);
	static VectorI2		Max(const VectorI2 & vec0, const VectorI2 & vec1);
	static VectorI2		Mix(const VectorI2 & vec0, const VectorI2 & vec1, const Bool2 & condition);



	int		Product() const;

	int			Convert(VectorI2 idx) const;
	VectorI2	Convert(int idx) const;

	static int			Convert(int size, VectorI2 idx);
	static VectorI2		Convert(int size, int idx);



	Bool2			operator==(const VectorI2 & other) const;
	Bool2			operator!=(const VectorI2 & other) const;
	Bool2			operator< (const VectorI2 & other) const;
	Bool2			operator> (const VectorI2 & other) const;
	Bool2			operator<=(const VectorI2 & other) const;
	Bool2			operator>=(const VectorI2 & other) const;

	VectorI2		operator+() const;
	VectorI2		operator-() const;

	VectorI2		operator+(const VectorI2 & other) const;
	VectorI2		operator-(const VectorI2 & other) const;
	VectorI2		operator*(const VectorI2 & other) const;
	VectorI2		operator/(const VectorI2 & other) const;

	VectorI2		operator%(const VectorI2 & other) const;

	VectorI2		operator~() const;

	VectorI2		operator&(const VectorI2 & other) const;
	VectorI2		operator|(const VectorI2 & other) const;
	VectorI2		operator^(const VectorI2 & other) const;

	VectorI2		operator<<(const VectorI2 & other) const;
	VectorI2		operator>>(const VectorI2 & other) const;

	VectorI2 &		operator+=(const VectorI2 & other);
	VectorI2 &		operator-=(const VectorI2 & other);
	VectorI2 &		operator*=(const VectorI2 & other);
	VectorI2 &		operator/=(const VectorI2 & other);

	VectorI2 &		operator+=(const int & val);
	VectorI2 &		operator-=(const int & val);
	VectorI2 &		operator*=(const int & val);
	VectorI2 &		operator/=(const int & val);
};

VectorI2		operator+(const VectorI2 & vec, const int & val);
VectorI2		operator-(const VectorI2 & vec, const int & val);
VectorI2		operator*(const VectorI2 & vec, const int & val);
VectorI2		operator/(const VectorI2 & vec, const int & val);

VectorI2		operator+(const int & val, const VectorI2 & vec);
VectorI2		operator-(const int & val, const VectorI2 & vec);
VectorI2		operator*(const int & val, const VectorI2 & vec);
VectorI2		operator/(const int & val, const VectorI2 & vec);

#endif
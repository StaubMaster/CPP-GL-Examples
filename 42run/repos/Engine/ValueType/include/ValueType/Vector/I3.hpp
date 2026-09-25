#ifndef  VECTOR_I_3_HPP
# define VECTOR_I_3_HPP

struct Bool3;
struct VectorU3;
struct VectorF3;

struct VectorI3
{
	int	X = 0;
	int	Y = 0;
	int	Z = 0;

	~VectorI3() = default;
	VectorI3() = default;
	VectorI3(const VectorI3 & other) = default;
	VectorI3 & operator=(const VectorI3 & other) = default;

	VectorI3(int x, int y, int z);
	VectorI3(int value);

	VectorU3	ToU() const;
	VectorF3	ToF() const;



	VectorI3	Min(const VectorI3 & other) const;
	VectorI3	Max(const VectorI3 & other) const;
	VectorI3	Mix(const VectorI3 & other, const Bool3 & condition) const;

	static VectorI3		Min(const VectorI3 & vec0, const VectorI3 & vec1);
	static VectorI3		Max(const VectorI3 & vec0, const VectorI3 & vec1);
	static VectorI3		Mix(const VectorI3 & vec0, const VectorI3 & vec1, const Bool3 & condition);



	int		Product() const;

	int			Convert(VectorI3 idx) const;
	VectorI3	Convert(int idx) const;

	static int			Convert(int size, VectorI3 idx);
	static VectorI3		Convert(int size, int idx);



	Bool3			operator==(const VectorI3 & other) const;
	Bool3			operator!=(const VectorI3 & other) const;
	Bool3			operator< (const VectorI3 & other) const;
	Bool3			operator> (const VectorI3 & other) const;
	Bool3			operator<=(const VectorI3 & other) const;
	Bool3			operator>=(const VectorI3 & other) const;

	VectorI3		operator+() const;
	VectorI3		operator-() const;

	VectorI3		operator+(const VectorI3 & other) const;
	VectorI3		operator-(const VectorI3 & other) const;
	VectorI3		operator*(const VectorI3 & other) const;
	VectorI3		operator/(const VectorI3 & other) const;

	VectorI3		operator%(const VectorI3 & other) const;

	VectorI3		operator~() const;

	VectorI3		operator&(const VectorI3 & other) const;
	VectorI3		operator|(const VectorI3 & other) const;
	VectorI3		operator^(const VectorI3 & other) const;

	VectorI3		operator<<(const VectorI3 & other) const;
	VectorI3		operator>>(const VectorI3 & other) const;

	VectorI3 &		operator+=(const VectorI3 & other);
	VectorI3 &		operator-=(const VectorI3 & other);
	VectorI3 &		operator*=(const VectorI3 & other);
	VectorI3 &		operator/=(const VectorI3 & other);

	VectorI3 &		operator+=(const int & val);
	VectorI3 &		operator-=(const int & val);
	VectorI3 &		operator*=(const int & val);
	VectorI3 &		operator/=(const int & val);
};

VectorI3		operator+(const VectorI3 & vec, const int & val);
VectorI3		operator-(const VectorI3 & vec, const int & val);
VectorI3		operator*(const VectorI3 & vec, const int & val);
VectorI3		operator/(const VectorI3 & vec, const int & val);

VectorI3		operator+(const int & val, const VectorI3 & vec);
VectorI3		operator-(const int & val, const VectorI3 & vec);
VectorI3		operator*(const int & val, const VectorI3 & vec);
VectorI3		operator/(const int & val, const VectorI3 & vec);

#endif
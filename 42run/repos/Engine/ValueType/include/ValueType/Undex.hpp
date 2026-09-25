#ifndef  UNDEX_HPP
# define UNDEX_HPP

struct Undex
{
	public:
	unsigned int Value;

	public:
	~Undex();
	Undex();
	Undex(unsigned int val);

	Undex(const Undex & other);
	Undex & operator=(const Undex & other);



	bool IsValid() const;
	static Undex Invalid();
	operator bool() const;



	Undex operator+(const Undex & other) const;
	Undex operator-(const Undex & other) const;
	Undex operator*(const Undex & other) const;
	Undex operator/(const Undex & other) const;
	Undex operator%(const Undex & other) const;

	Undex operator+(unsigned int value) const;
	Undex operator-(unsigned int value) const;
	Undex operator*(unsigned int value) const;
	Undex operator/(unsigned int value) const;
	Undex operator%(unsigned int value) const;

	Undex & operator+=(const Undex & other);
	Undex & operator-=(const Undex & other);
	Undex & operator*=(const Undex & other);
	Undex & operator/=(const Undex & other);
	Undex & operator%=(const Undex & other);

	Undex & operator+=(unsigned int value);
	Undex & operator-=(unsigned int value);
	Undex & operator*=(unsigned int value);
	Undex & operator/=(unsigned int value);
	Undex & operator%=(unsigned int value);

	Undex & operator++();
	Undex & operator--();

	Undex operator++(int);
	Undex operator--(int);

	bool operator==(const Undex & other) const;
	bool operator<=(const Undex & other) const;
	bool operator>=(const Undex & other) const;
	bool operator!=(const Undex & other) const;
	bool operator<(const Undex & other) const;
	bool operator>(const Undex & other) const;
};

#endif
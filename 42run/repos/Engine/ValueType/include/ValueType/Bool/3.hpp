#ifndef  BOOL_3_HPP
# define BOOL_3_HPP

struct Bool3
{
	private:
	unsigned char Bits;
	Bool3(unsigned char bits);



	public:
	bool	GetX() const;
	bool	GetY() const;
	bool	GetZ() const;

	void	SetX(bool value);
	void	SetY(bool value);
	void	SetZ(bool value);

	bool	All(bool value) const;
	bool	Any(bool value) const;

	unsigned char	Count(bool value)const;



	public:
	~Bool3();

	Bool3();
	Bool3(bool value);
	Bool3(bool x, bool y, bool z);
	
	Bool3(const Bool3 & other);
	Bool3 & operator=(const Bool3 & other);



	public:
	Bool3 operator!() const;
	Bool3 operator&(const Bool3 & other) const;
	Bool3 operator|(const Bool3 & other) const;
	Bool3 operator^(const Bool3 & other) const;

	bool operator==(const Bool3 & other) const;
	bool operator!=(const Bool3 & other) const;

	bool operator&(bool value) const;
	bool operator|(bool value) const;
	bool operator^(bool value) const;
};

#endif
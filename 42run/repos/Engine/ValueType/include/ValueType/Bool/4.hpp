#ifndef  BOOL_4_HPP
# define BOOL_4_HPP

struct Bool4
{
	private:
	unsigned char Bits;
	Bool4(unsigned char bits);



	public:
	bool	GetX() const;
	bool	GetY() const;
	bool	GetZ() const;
	bool	GetW() const;

	void	SetX(bool value);
	void	SetY(bool value);
	void	SetZ(bool value);
	void	SetW(bool value);

	bool	All(bool value) const;
	bool	Any(bool value) const;

	unsigned char	Count(bool value) const;



	public:
	~Bool4();

	Bool4();
	Bool4(bool value);
	Bool4(bool x, bool y, bool z, bool w);
	
	Bool4(const Bool4 & other);
	Bool4 & operator=(const Bool4 & other);



	public:
	Bool4 operator!() const;
	Bool4 operator&(const Bool4 & other) const;
	Bool4 operator|(const Bool4 & other) const;
	Bool4 operator^(const Bool4 & other) const;

	bool operator==(const Bool4 & other) const;
	bool operator!=(const Bool4 & other) const;

	bool operator&(bool value) const;
	bool operator|(bool value) const;
	bool operator^(bool value) const;
};

#endif
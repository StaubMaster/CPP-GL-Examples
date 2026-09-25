#ifndef  COMPARISON_1D_HPP
# define COMPARISON_1D_HPP

struct Comparison1D
{
	private:
	unsigned char Bits;

	public:
	Comparison1D();
	Comparison1D(bool smaller, bool equal, bool greater);
	~Comparison1D();

	Comparison1D(const Comparison1D & other);
	Comparison1D & operator=(const Comparison1D & other);

	public:
	bool operator==(const Comparison1D & other);



	public:
	bool GetSmaller() const;
	bool GetEqual() const;
	bool GetGreater() const;

	public:
	void SetSmaller(bool val);
	void SetEqual(bool val);
	void SetGreater(bool val);
};

#endif
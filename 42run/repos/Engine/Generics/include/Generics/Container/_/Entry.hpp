#ifndef  CONTAINER_ENTRY_HPP
# define CONTAINER_ENTRY_HPP

namespace Container
{

struct Entry
{
	public:
	unsigned int Offset;
	unsigned int Length;

	public:
	unsigned int Min() const { return Offset; }
	unsigned int Max() const { return (Offset + Length) - 1; }
	unsigned int Limit() const { return Offset + Length; }

	bool	IsEmpty() const { return (Offset == 0) && (Length == 0); }
	void	MakeEmpty() { Offset = 0; Length = 0; }

	public:
	virtual void DebugInfo() { }

	public:
	Entry() :
		Offset(0),
		Length(0)
	{ }
	Entry(unsigned int off, unsigned int len) :
		Offset(off),
		Length(len)
	{ }
	virtual ~Entry()
	{ }

	public:
	Entry(const Entry & other) :
		Offset(other.Offset),
		Length(other.Length)
	{ }
	Entry & operator =(const Entry & other)
	{
		Offset = other.Offset;
		Length = other.Length;
		return *this;
	}

	/*	Memory Reordering ?
		Copy Input Data with Gaps onto Output Data with Gaps
		Invert Entrys ?
			the Entrys become Gaps
			the Gaps become Entrys
	*/
};

};

#endif
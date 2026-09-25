#ifndef  CONTAINER_BINARY_HPP
# define CONTAINER_BINARY_HPP

# include "Array.hpp"

namespace Container
{
// calling this a Binary sounds like this is an executable file
template<typename TypeItem> struct Binary
{
	private:
	Array<TypeItem>		mData;
	unsigned long		mUsed = 0;

	public:
	bool			IsNull() const		{ return (mData.IsNull()); }

	public:
	unsigned long	Limit() const	{ return mData.Length(); }
	unsigned long	Count() const	{ return mUsed; }

	public:
	bool			Check(unsigned long idx) const	{ return (idx < mUsed); }

	public:
	const	TypeItem &	At(unsigned long idx) const	{ return mData.At(idx); }
			TypeItem &	At(unsigned long idx)		{ return mData.At(idx); }

	public:
	const	TypeItem &	operator[](unsigned long idx) const	{ if (Check(idx)) { return At(idx); } throw Container::Exception::InvalidIndex(); }
			TypeItem &	operator[](unsigned long idx)		{ if (Check(idx)) { return At(idx); } throw Container::Exception::InvalidIndex(); }

	public:
	Array<TypeItem>		ToArray() const
	{
		Array<TypeItem> array = mData;
		array.AssignLength(mUsed);
		return array;
	}
	Void	ToVoid() const
	{
		Void v;
		v.Size = mUsed * sizeof(TypeItem);
		v.Data = mData.Memory();
		return v;
	}

	public:
	~Binary()
	{ }
	Binary()
	{ }

	public:
	Binary(const Binary & other)
		: mData(other.mData)
		, mUsed(other.mUsed)
	{ }
	Binary & operator=(const Binary & other)
	{
		mData = other.mData;
		mUsed = other.mUsed;
		return *this;
	}

	public:
	void	Clear()
	{
		mData.Clear();
		mUsed = 0;
	}

	private:
	unsigned long	CalculateBinarySize(unsigned long wanted)
	{
		for (unsigned char shift = 63; shift < 64; shift--)
		{
			unsigned long size = 0xFFFFFFFFFFFFFFFF >> shift;
			if (size >= wanted)
			{
				return size;
			}
		}
		return 0;
	}

	public:
	void	Trim()
	{
		mData.NewLengthHere(mUsed);
	}
	void	MakeNativeSize()
	{
		mData.NewLengthHere(CalculateBinarySize(mUsed));
	}

	public:
	void	Insert(const TypeItem & item)
	{
		unsigned int newCount = mUsed + 1;
		unsigned int newLimit = CalculateBinarySize(newCount);

		mData.Seperate();

		if (mData.Length() != newLimit)
		{
			mData.NewLengthHere(newLimit);
		}

		if (newCount <= mData.Length())
		{
			mData.At(mUsed) = item;
			mUsed = newCount;
		}
	}
	void	RemoveAt(unsigned long idx)
	{
		if (idx >= mUsed)
		{
			throw Container::Exception::InvalidIndex();
		}

		unsigned int newCount = mUsed - 1;
		unsigned int newLimit = CalculateBinarySize(newCount);

		mData.Seperate();

		// remove gap
		for (unsigned long i = idx; (i + 1) < mUsed; i++)
		{
			mData.At(i) = mData.At(i + 1);
		}

		if (mData.Length() != newLimit)
		{
			mData.NewLengthHere(newLimit);
		}
		mUsed = newCount;
	}
};
};

#endif
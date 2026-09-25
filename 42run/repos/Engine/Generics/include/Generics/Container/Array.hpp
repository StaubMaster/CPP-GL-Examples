#ifndef  CONTAINER_ARRAY_HPP
# define CONTAINER_ARRAY_HPP

# include "Exception.hpp"
# include <initializer_list>
# include "Void.hpp"

namespace Container
{
template<typename TypeItem> struct Array
{
	private:
	TypeItem *			mMemory = nullptr;
	unsigned long *		mShared = nullptr;
	unsigned long		mLength = 0;

	public:
	bool	IsNull() const		{ return (mMemory == nullptr); }
	bool	IsShared() const	{ return (mShared != nullptr && (*mShared) != 0); }

	public:
	const	TypeItem *	Memory() const	{ return mMemory; }
			TypeItem *	Memory()		{ return mMemory; }

	public:
	unsigned long	Length() const					{ return mLength; }
	bool			Check(unsigned long idx) const	{ return (idx < mLength); }

	public:
	const	TypeItem &	At(unsigned long idx) const	{ return mMemory[idx]; }
			TypeItem &	At(unsigned long idx)		{ return mMemory[idx]; }

	public:
	const	TypeItem &	operator[](unsigned long idx) const	{ if (Check(idx)) { return At(idx); } throw Container::Exception::InvalidIndex(); }
			TypeItem &	operator[](unsigned long idx)		{ if (Check(idx)) { return At(idx); } throw Container::Exception::InvalidIndex(); }

	public:
	Void	ToVoid() const
	{
		Void v;
		v.Size = mLength * sizeof(TypeItem);
		v.Data = mMemory;
		return v;
	}

	private:
	void	mDefault()
	{
		mMemory = nullptr;
		mShared = nullptr;
		mLength = 0;
	}
	void	mDelete()
	{
		if (mShared != nullptr)
		{
			if ((*mShared) == 0)
			{
				delete mShared;
				delete[] mMemory;
			}
			else
			{
				(*mShared)--;
			}
		}
	}
	void	mNew(unsigned long len)
	{
		mMemory = new TypeItem[len];
		mShared = new unsigned long; (*mShared) = 0;
		mLength = len;
	}
	void	mAssign(unsigned long len, TypeItem * data)
	{
		mMemory = data;
		mShared = nullptr;
		mLength = len;
	}

	private:
	void	mBind(const Array & other)
	{
		mMemory = other.mMemory;
		mShared = other.mShared;
		mLength = other.mLength;
		if (mShared != nullptr) { (*mShared)++; }
	}
	void	mCopy(const Array & other)
	{
		unsigned long n = mLength;
		if (n > other.mLength) { n = other.mLength; }
		for (unsigned long i = 0; i < n; i++)
		{
			mMemory[i] = other.mMemory[i];
		}
	}

	public:
	~Array()
	{
		mDelete();
	}
	Array()
	{
	}
	Array(unsigned long len)
	{
		mNew(len);
	}
	Array(unsigned long len, const TypeItem & default_item)
	{
		mNew(len);
		AssignAll(default_item);
	}

	public:
	Array(unsigned long len, TypeItem * data)
	{
		mAssign(len, data);
	}
	Array(unsigned long len, const TypeItem * data)
	{
		mAssign(len, (TypeItem*)data);
	}

	public:
	Array(std::initializer_list<TypeItem> list)
	{
		mNew(list.size());
		const TypeItem * ptr = list.begin();
		for (unsigned int i = 0; i < mLength; i++)
		{
			mMemory[i] = ptr[i];
		}
	}

	public:
	Array(const Array & other)
	{
		mBind(other);
	}
	Array & operator=(const Array & other)
	{
		mDelete();
		mBind(other);
		return *this;
	}



	public:
	void	Clear()
	{
		mDelete();
		mDefault();
	}
	void	AssignAll(const TypeItem & default_item)
	{
		for (unsigned long i = 0; i < mLength; i++)
		{
			mMemory[i] = default_item;
		}
	}

	public:
	void	NewLength(unsigned long len)
	{
		mDelete();
		mNew(len);
	}
	void	NewLength(unsigned long len, const TypeItem & default_item)
	{
		mDelete();
		mNew(len);
		AssignAll(default_item);
	}
	void	NewLengthHere(unsigned long len)
	{
		Array temp(*this);
		mDelete();
		mNew(len);
		mCopy(temp);
	}
	void	AssignLength(unsigned long len)
	{
		mLength = len;
	}

	public:
	void	Seperate()
	{
		if (IsShared())
		{
			Array temp(*this);
			mDelete();
			mNew(temp.Length());
			mCopy(temp);
		}
	}



	public:
	void		Bind(const Array & other)
	{
		mDelete();
		mBind(other);
	}
	void		Copy(const Array & other)
	{
		mDelete();
		mNew(other.mLength);
		mCopy(other);
	}
	Array		Bind() const
	{
		Array other;
		other.Bind(*this);
		return other;
	}
	Array		Copy() const
	{
		Array other;
		other.Copy(*this);
		return other;
	}
};
};

#endif
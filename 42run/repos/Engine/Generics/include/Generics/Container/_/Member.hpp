#ifndef  CONTAINER_MEMBBER_HPP
# define CONTAINER_MEMBBER_HPP

# include "Void.hpp"
# include "Exception.hpp"

# include "ValueType/Undex.hpp"

//# define DEBUG_MESSAGES
# ifdef DEBUG_MESSAGES
#  include <iostream>
# endif



template<typename T>
static void swap(T & a, T & b)
{
	T t;
	t = a;
	a = b;
	b = t;
}



namespace Container
{

template<typename T>
class Member : public Void
{
	protected:
	unsigned int	_Limit;
	unsigned int	_Count;
	T *				_Data;



	public:
	unsigned int VoidLimit() const override { return _Limit * sizeof(T); }
	unsigned int VoidCount() const override { return _Count * sizeof(T); }

	const void * VoidData() const override { return _Data; }
	void * VoidData() override { return _Data; }



	public:
	unsigned int Limit() const override { return _Limit; }
	unsigned int Count() const override { return _Count; }

	const T * Data() const { return _Data; }
	T * Data() { return _Data; }

	const T & At(unsigned int idx) const { return _Data[idx]; }
	T & At(unsigned int idx) { return _Data[idx]; }

	const T & operator[](unsigned int idx) const
	{
		if (idx >= _Count) { throw Exception::InvalidIndex(); }
		return _Data[idx];
	}
	T & operator[](unsigned int idx)
	{
		if (idx >= _Count) { throw Exception::InvalidIndex(); }
		return _Data[idx];
	}



	const T & At(const Undex & udx) const { return _Data[udx.Value]; }
	T & At(const Undex & udx) { return _Data[udx.Value]; }

	const T & operator[](const Undex & udx) const
	{
		if (udx.Value >= _Count) { throw Exception::InvalidIndex(); }
		return _Data[udx.Value];
	}
	T & operator[](const Undex & udx)
	{
		if (udx.Value >= _Count) { throw Exception::InvalidIndex(); }
		return _Data[udx.Value];
	}



	public:
	unsigned int MinIndex() const { return 0; }
	unsigned int MaxIndex() const { if (_Count != 0) { return _Count - 1; } return 0; }

	const T & MinItem() const { return operator[](MinIndex()); }
	const T & MaxItem() const { return operator[](MaxIndex()); }

	T & MinItem() { return operator[](MinIndex()); }
	T & MaxItem() { return operator[](MaxIndex()); }



	public:
	Member() :
		_Limit(0),
		_Count(0),
		_Data(nullptr)
	{ }
	~Member()
	{ }

	public:
	Member(const Member & other) :
		_Limit(other._Limit),
		_Count(other._Count),
		_Data(other._Data)
	{
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Member(other)\n";
# endif
	}
	Member & operator=(const Member & other)
	{
		_Limit = other._Limit;
		_Count = other._Count;
		_Data = other._Data;
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Member::operator=(other)\n";
# endif
		return *this;
	}



	protected:
	void mForget()
	{
		_Limit = 0;
		_Count = 0;
		_Data = nullptr;
	}
	void mDelete()
	{
		delete[] _Data;
		mForget();
	}

	protected:
	public:
	void mTransfer(const Member<T> & other)
	{
		if (other._Count < _Count)
		{
			_Count = other._Count;
		}
		for (unsigned int i = 0; i < _Count; i++)
		{
			_Data[i] = other._Data[i];
		}
	}
	void mRemember(const T * data, unsigned int limit, unsigned int count)
	{
		_Limit = limit;
		_Count = count;
		_Data = (T*)data;
	}
	void mAllocate(unsigned int limit, unsigned int count)
	{
		_Limit = limit;
		_Count = count;
		_Data = new T[limit];
	}

	public:
	void Swap(Member<T> & other)
	{
		swap(_Limit, other._Limit);
		swap(_Count, other._Count);
		swap(_Data, other._Data);
	}

	protected:
	void mBind(const Member<T> & other)
	{
		mRemember(other._Data, other._Limit, other._Count);
	}
	void mCopy(const Member<T> & other)
	{
		mAllocate(other._Limit, other._Count);
		mTransfer(other);
	}
};
};

#endif
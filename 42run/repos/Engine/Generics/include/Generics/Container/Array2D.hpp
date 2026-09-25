#ifndef  CONTAINER_ARRAY_2D_HPP
# define CONTAINER_ARRAY_2D_HPP

# include "ValueType/Vector/U2.hpp"
# include "ValueType/Bool/2.hpp"
# include "Exception.hpp"

template<typename ItemType> struct Array2D
{
	private:
	ItemType *		_Data = nullptr;
	unsigned int *	_Know = nullptr;
	VectorU2		_Size;

	public:
	bool				IsNull() const	{ return (_Data == nullptr); }
			ItemType *	Data()			{ return _Data; }
	const	ItemType *	Data() const	{ return _Data; }

	public:
	VectorU2		Size() const	{ return _Size; }
	unsigned int	Length() const	{ return _Size.Product(); }

	public:
	bool			Check(unsigned int idx) const	{ return (idx < Length()); }
	bool			Check(VectorU2 idx) const		{ return (idx < _Size).All(true); }

	public:
			ItemType &	At(unsigned int idx)		{ return _Data[idx]; }
	const	ItemType &	At(unsigned int idx) const	{ return _Data[idx]; }
			ItemType &	At(VectorU2 idx)			{ return _Data[_Size.Convert(idx)]; }
	const	ItemType &	At(VectorU2 idx) const		{ return _Data[_Size.Convert(idx)]; }

	public:
			ItemType &	operator[](unsigned int idx)		{ if (Check(idx)) { return At(idx); } throw Container::Exception::InvalidIndex(); }
	const	ItemType &	operator[](unsigned int idx) const	{ if (Check(idx)) { return At(idx); } throw Container::Exception::InvalidIndex(); }
			ItemType &	operator[](VectorU2 idx)			{ if (Check(idx)) { return At(idx); } throw Container::Exception::InvalidIndex(); }
	const	ItemType &	operator[](VectorU2 idx) const		{ if (Check(idx)) { return At(idx); } throw Container::Exception::InvalidIndex(); }

	private:
	void	mDefault()
	{
		_Data = nullptr;
		_Know = nullptr;
		_Size = VectorU2();
	}
	void	mDelete()
	{
		if (_Know != nullptr)
		{
			if ((*_Know) == 0)
			{
				delete _Know;
				delete[] _Data;
			}
			else
			{
				(*_Know)--;
			}
		}
	}
	void	mNew(VectorU2 size)
	{
		_Data = new ItemType[size.Product()];
		_Know = new unsigned int; (*_Know) = 0;
		_Size = size;
	}

	private:
	void	mBind(const Array2D & other)
	{
		_Data = other._Data;
		_Know = other._Know;
		_Size = other._Size;
		if (_Know != nullptr) { (*_Know)++; }
	}
	void	mCopy(const Array2D & other)
	{
		unsigned int n = _Size.Product();
		if (n < other._Size.Product()) { n = other._Size.Product(); }
		for (unsigned int i = 0; i < n; i++)
		{
			_Data[i] = other._Data[i];
		}
	}

	public:
	~Array2D()
	{
		mDelete();
	}
	Array2D()
	{
	}
	Array2D(VectorU2 size)
	{
		mNew(size);
	}
	Array2D(VectorU2 size, const ItemType & default_item)
	{
		mNew(size);
		ChangeAll(default_item);
	}

	public:
	Array2D(const Array2D & other)
	{
		mBind(other);
	}
	Array2D & operator=(const Array2D & other)
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

	public:
	void	Size(VectorU2 size)
	{
		mDelete();
		mNew(size);
	}
	void	Size(VectorU2 size, const ItemType & default_item)
	{
		mDelete();
		mNew(size);
		ChangeAll(default_item);
	}

	public:
	void		Bind(const Array2D & other)
	{
		mDelete();
		mBind(other);
	}
	void		Copy(const Array2D & other)
	{
		mDelete();
		mNew(other._Size);
		mCopy(other);
	}
	Array2D		Bind() const
	{
		Array2D other;
		other.Bind(*this);
		return other;
	}
	Array2D		Copy() const
	{
		Array2D other;
		other.Copy(*this);
		return other;
	}
};

#endif
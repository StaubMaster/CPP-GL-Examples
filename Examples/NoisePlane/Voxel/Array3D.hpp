#ifndef  ARRAY_3D_HPP
# define ARRAY_3D_HPP

# include "ValueType/VectorU3.hpp"

template<typename ItemType>
struct Array3D
{
	ItemType *			_Data;
	VectorU3			_Size;

	VectorU3			Size() const { return _Size; }
	unsigned int		Count() const { return _Size.Product(); }
	// Length ?
	// Count and Limit are for Dynamic Containers
	// Size and Length are for fixed Containers

	ItemType &			operator[](unsigned int idx) { return _Data[idx]; }
	ItemType &			operator[](VectorU3 idx) { return _Data[_Size.Convert(idx)]; }

	const ItemType &	operator[](unsigned int idx) const { return _Data[idx]; }
	const ItemType &	operator[](VectorU3 idx) const { return _Data[_Size.Convert(idx)]; }

	~Array3D()
	{
		delete[] _Data;
	}
	Array3D()
		: _Data(nullptr)
		, _Size()
	{ }

	Array3D(const Array3D & other) = delete;
	Array3D & operator=(const Array3D & other) = delete;

	void	Clear()
	{
		delete[] _Data;
		_Data = nullptr;
		_Size = VectorU3();
	}
	void	ReSize(VectorU3 size)
	{
		delete[] _Data;
		_Data = new ItemType[size.Product()];
		_Size = size;
	}
};

#endif
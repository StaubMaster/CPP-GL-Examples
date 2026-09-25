#ifndef  CONTAINER_ARRAY_HPP
# define CONTAINER_ARRAY_HPP

# include "Base.hpp"
# include <initializer_list>



namespace Container
{

template<typename T>
class Array : public Base<T>
{
	public:
	Array() : Base<T>()
	{ }
	~Array()
	{
		Clear();
	}
	Array(unsigned int limit) : Base<T>()
	{
		this -> mAllocate(limit, limit);
	}
	Array(std::initializer_list<T> list) : Base<T>()
	{
		this -> mAllocate(list.size(), list.size());
		const T * ptr = list.begin();
		for (unsigned int i = 0; i < this -> _Limit; i++)
		{
			this -> _Data[i] = ptr[i];
		}
	}

	Array(const Array<T> & other) : Base<T>()
	{
		this -> mAssign(other);
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Array(other)\n";
# endif
	}
	Array & operator=(const Array<T> & other)
	{
		this -> Assign(other);
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Array::operator=(other)\n";
# endif
		return *this;
	}
	Array(const Member<T> & other) : Base<T>()
	{
		this -> mAssign(other);
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Array(other)\n";
# endif
	}
	Array & operator=(const Member<T> & other)
	{
		this -> Assign(other);
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Array::operator=(other)\n";
# endif
		return *this;
	}

	public:
	void	List(std::initializer_list<T> list)
	{
		this -> Allocate(list.size(), list.size());
		const T * ptr = list.begin();
		for (unsigned int i = 0; i < this -> _Limit; i++)
		{
			this -> _Data[i] = ptr[i];
		}
	}

	public:
	void	Clear() override
	{
		this -> mDelete();
	}
	protected:
	void	mAssign(const Member<T> other) override
	{
		this -> mCopy(other);
	}

	public:
	using Base<T>::Bind;
	using Base<T>::Copy;

	public:
	Array<T> Bind() const
	{
		Array<T> other;
		other.Bind(*this);
		return other;
	}
	Array<T> Copy() const
	{
		Array<T> other;
		other.Copy(*this);
		return other;
	}

	protected:
	unsigned int	CalcLimit(unsigned int wanted_count) override
	{
		(void)wanted_count;
		return this -> _Limit;
	}
};
};

#endif
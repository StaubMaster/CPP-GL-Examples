#ifndef  CONTAINER_FIXED_HPP
# define CONTAINER_FIXED_HPP

# include "Base.hpp"



namespace Container
{

template<typename T>
class Fixed : public Base<T>
{
	public:
	Fixed() : Base<T>()
	{ }
	Fixed(unsigned int limit) : Base<T>()
	{
		this -> mAllocate(limit, 0);
	}
	~Fixed()
	{
		Clear();
	}

	Fixed(const Fixed<T> & other) : Base<T>()
	{
		this -> mAssign(other);
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Fixed(other)\n";
# endif
	}
	Fixed & operator=(const Fixed<T> & other)
	{
		this -> Assign(other);
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Fixed::operator=(other)\n";
# endif
		return *this;
	}
	Fixed(const Member<T> & other) : Base<T>()
	{
		this -> mAssign(other);
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Fixed(other)\n";
# endif
	}
	Fixed & operator=(const Member<T> & other)
	{
		this -> Assign(other);
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Fixed::operator=(other)\n";
# endif
		return *this;
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
	Fixed<T> Bind() const
	{
		Fixed<T> other;
		other.Bind(*this);
		return other;
	}
	Fixed<T> Copy() const
	{
		Fixed<T> other;
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
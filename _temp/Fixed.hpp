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
		this -> Allocate(limit, 0);
	}
	~Fixed()
	{ }

	Fixed(const Fixed<T> & other) = delete;
	Fixed & operator=(const Fixed<T> & other) = delete;

	void	Clear() override
	{
		this -> mDelete();
	}

	unsigned int	CalcLimit(unsigned int wanted_count) override
	{
		(void)wanted_count;
		return this -> _Limit;
	}
};
};

#endif
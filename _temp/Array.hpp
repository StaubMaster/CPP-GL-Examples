#ifndef  CONTAINER_ARRAY_HPP
# define CONTAINER_ARRAY_HPP

# include "Base.hpp"



namespace Container
{

template<typename T>
class Array : public Base<T>
{
	public:
	Array() : Base<T>()
	{ }
	Array(unsigned int limit) : Base<T>()
	{
		this -> Allocate(limit, limit);
	}
	~Array()
	{ }

	Array(const Array<T> & other) = delete;
	Array & operator=(const Array<T> & other) = delete;

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
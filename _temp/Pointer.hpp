#ifndef  CONTAINER_POINTER_HPP
# define CONTAINER_POINTER_HPP

# include "Base.hpp"



namespace Container
{

template<typename T>
class Pointer : public Base<T>
{
	public:
	Pointer() : Base<T>()
	{ }
	Pointer(const T * data, unsigned int limit) : Base<T>()
	{
		this -> Remember((T*)data, limit, limit);
	}
	Pointer(const T * data, unsigned int limit, unsigned int count) : Base<T>()
	{
		this -> Remember((T*)data, limit, count);
	}
	Pointer(Member<T> & other) : Base<T>()
	{
		this -> mBind(other);
	}
	~Pointer()
	{ }

	Pointer(const Pointer<T> & other) = delete;
	Pointer & operator=(const Pointer<T> & other) = delete;

	void	Clear() override
	{
		this -> mForget();
	}

	unsigned int	CalcLimit(unsigned int wanted_count) override
	{
		(void)wanted_count;
		return this -> _Limit;
	}
};
};

#endif
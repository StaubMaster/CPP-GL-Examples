#ifndef  CONTAINER_TIGHT_HPP
# define CONTAINER_TIGHT_HPP

# include "Base.hpp"



namespace Container
{

template<typename T>
class Tight : public Base<T>
{
	public:
	Tight() : Base<T>()
	{ }
	~Tight()
	{ }

	Tight(const Tight<T> & other) = delete;
	Tight & operator=(const Tight<T> & other) = delete;

	void	Clear() override
	{
		this -> mDelete();
	}

	unsigned int	CalcLimit(unsigned int wanted_count) override
	{
		return wanted_count;
	}
};
};

#endif
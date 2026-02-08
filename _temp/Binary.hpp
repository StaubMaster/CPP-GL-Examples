#ifndef  CONTAINER_BINARY_HPP
# define CONTAINER_BINARY_HPP

# include "Base.hpp"



namespace Container
{

template<typename T>
class Binary : public Base<T>
{
	public:
	Binary() : Base<T>()
	{ }
	~Binary()
	{ }

	Binary(const Binary<T> & other) = delete;
	Binary & operator=(const Binary<T> & other) = delete;

	void	Clear() override
	{
		this -> mDelete();
	}

	unsigned int	CalcLimit(unsigned int wanted_count) override
	{
		for (unsigned char shift = 31; shift < 32; shift--)
		{
			unsigned int size = 0xFFFFFFFF >> shift;
			if (size >= wanted_count)
			{
				return size;
			}
		}
		return 0;
	}
};
};

#endif
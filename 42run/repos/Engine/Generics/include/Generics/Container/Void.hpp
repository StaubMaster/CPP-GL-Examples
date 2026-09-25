#ifndef  CONTAINER_VOID_HPP
# define CONTAINER_VOID_HPP

namespace Container
{
struct Void
{
	unsigned long	Size = 0;
	const void *	Data = nullptr;

	bool	IsNull() const;
	void	Clear();

	~Void() = default;
	Void() = default;
	Void(const Void & other) = default;
	Void & operator=(const Void & other) = default;

	template<typename Type> Void(const Type * data)
		: Size(sizeof(Type))
		, Data(data)
	{ }
	template<typename Type> Void(const Type & data)
		: Size(sizeof(Type))
		, Data(&data)
	{ }

	template<typename Type> Void & operator=(const Type * data)
	{
		Size = sizeof(Type);
		Data = data;
		return *this;
	}
	template<typename Type> Void & operator=(const Type & data)
	{
		Size = sizeof(Type);
		Data = &data;
		return *this;
	}
};
};

#endif
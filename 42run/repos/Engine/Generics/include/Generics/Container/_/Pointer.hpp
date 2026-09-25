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
		this -> mRemember((T*)data, limit, limit);
	}
	Pointer(const T * data, unsigned int limit, unsigned int count) : Base<T>()
	{
		this -> mRemember((T*)data, limit, count);
	}
	Pointer(unsigned int limit) : Base<T>()
	{
		this -> mAllocate(limit, limit);
	}
	Pointer(unsigned int limit, unsigned int count) : Base<T>()
	{
		this -> mAllocate(limit, count);
	}
	Pointer(Member<T> & other) : Base<T>()
	{
		this -> mBind(other);
	}
	~Pointer()
	{
		Clear();
	}

	Pointer(const Pointer<T> & other) : Base<T>()
	{
		this -> mAssign(other);
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Pointer(other)\n";
# endif
	}
	Pointer & operator=(const Pointer<T> & other)
	{
		this -> Assign(other);
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Pointer::operator=(other)\n";
# endif
		return *this;
	}
	Pointer(const Member<T> & other) : Base<T>()
	{
		this -> mAssign(other);
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Pointer(other)\n";
# endif
	}
	Pointer & operator=(const Member<T> & other)
	{
		this -> Assign(other);
# ifdef DEBUG_MESSAGES
		std::cout << __FILE__ << ':' << __LINE__ << ' ' << "Container::Pointer::operator=(other)\n";
# endif
		return *this;
	}

	public:
	void	Clear() override
	{
		this -> mForget();
	}
	protected:
	void	mAssign(const Member<T> other) override
	{
		this -> mBind(other);
	}

	public:
	using Base<T>::Bind;
	using Base<T>::Copy;

	public:
	Pointer<T> Bind() const
	{
		Pointer<T> other;
		other.Bind(*this);
		return other;
	}
	Pointer<T> Copy() const
	{
		Pointer<T> other;
		other.Copy(*this);
		return other;
	}

	protected:
	unsigned int	CalcLimit(unsigned int wanted_count) override
	{
		(void)wanted_count;
		return this -> _Limit;
	}

	public:
	void Forget()
	{
		this -> mForget();
	}
	void Delete()
	{
		this -> mDelete();
	}
};
};

#endif
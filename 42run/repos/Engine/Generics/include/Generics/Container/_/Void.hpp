#ifndef  CONTAINER_VOID_HPP
# define CONTAINER_VOID_HPP

namespace Container
{
class Void
{
	public:
	virtual unsigned int VoidLimit() const = 0;
	virtual unsigned int VoidCount() const = 0;

	virtual const void * VoidData() const = 0;
	virtual void * VoidData() = 0;

	public:
	virtual unsigned int Limit() const = 0;
	virtual unsigned int Count() const = 0;

	//virtual void Delete() = 0;
};
};

#endif
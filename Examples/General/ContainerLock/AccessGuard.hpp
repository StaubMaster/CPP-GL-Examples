#ifndef  CONTAINER_ACCESS_GUARD_HPP
# define CONTAINER_ACCESS_GUARD_HPP

struct ContainerLock;

struct ContainerAccessGuard
{
	protected:
	unsigned int *	Count;
	ContainerLock *	Lock;

	public:
	bool	Is() const;

	public:
	~ContainerAccessGuard();
	ContainerAccessGuard();
	ContainerAccessGuard(const ContainerAccessGuard & other);
	ContainerAccessGuard & operator=(const ContainerAccessGuard & other);

	protected:
	ContainerAccessGuard(ContainerLock & lock);
};

#endif
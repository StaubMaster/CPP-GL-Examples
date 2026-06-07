#ifndef  CONTAINER_ASSIGN_GUARD_HPP
# define CONTAINER_ASSIGN_GUARD_HPP

struct ContainerLock;

struct ContainerAssignGuard
{
	protected:
	unsigned int *	Count;
	ContainerLock *	Lock;

	public:
	bool	Is() const;

	public:
	~ContainerAssignGuard();
	ContainerAssignGuard();
	ContainerAssignGuard(const ContainerAssignGuard & other);
	ContainerAssignGuard & operator=(const ContainerAssignGuard & other);

	protected:
	ContainerAssignGuard(ContainerLock & lock);
};

#endif
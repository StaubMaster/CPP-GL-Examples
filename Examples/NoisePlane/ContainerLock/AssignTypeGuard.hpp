#ifndef  CONTAINER_ASSIGN_TYPE_GUARD_HPP
# define CONTAINER_ASSIGN_TYPE_GUARD_HPP

#include "ContainerLock/AssignGuard.hpp"
#include "ContainerLock/Lock.hpp"

template<typename TypeObject>
struct ContainerAssignTypeGuard : public ContainerAssignGuard
{
	private:
	TypeObject *	Object;

	public:
	TypeObject & operator*() { return (*Object); }

	public:
	~ContainerAssignTypeGuard()
	{ }
	ContainerAssignTypeGuard()
		: ContainerAssignGuard()
		, Object(nullptr)
	{ }
	ContainerAssignTypeGuard(const ContainerAssignTypeGuard & other)
		: ContainerAssignGuard(other)
		, Object(other.Object)
	{ }
	ContainerAssignTypeGuard & operator=(const ContainerAssignTypeGuard & other)
	{
		ContainerAssignGuard::operator=(other);
		Object = other.Object;
		return *this;
	}

	protected:
	ContainerAssignTypeGuard(ContainerLock & lock, TypeObject & obj)
		: ContainerAssignGuard(lock)
		, Object(&obj)
	{
		if (Lock == nullptr)
		{
			Object = nullptr;
		}
	}

	public:
	static ContainerAssignTypeGuard TakeLock(ContainerLock & lock, TypeObject & obj)
	{
		return ContainerAssignTypeGuard(lock, obj);
	}
};

#endif
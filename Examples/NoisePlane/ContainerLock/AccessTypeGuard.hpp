#ifndef  CONTAINER_ACCESS_TYPE_GUARD_HPP
# define CONTAINER_ACCESS_TYPE_GUARD_HPP

#include "ContainerLock/AccessGuard.hpp"
#include "ContainerLock/Lock.hpp"

template<typename TypeObject>
struct ContainerAssignTypeGuard;

template<typename TypeObject>
struct ContainerAccessTypeGuard : public ContainerAccessGuard
{
	private:
	TypeObject *	Object;

	public:
	const TypeObject & operator*() const { return (*Object); }

	public:
	~ContainerAccessTypeGuard()
	{ }
	ContainerAccessTypeGuard()
		: ContainerAccessGuard()
		, Object(nullptr)
	{ }
	ContainerAccessTypeGuard(const ContainerAccessTypeGuard & other)
		: ContainerAccessGuard(other)
		, Object(other.Object)
	{ }
	ContainerAccessTypeGuard & operator=(const ContainerAccessTypeGuard & other)
	{
		ContainerAccessGuard::operator=(other);
		Object = other.Object;
		return *this;
	}

	protected:
	ContainerAccessTypeGuard(ContainerLock & lock, TypeObject & obj)
		: ContainerAccessGuard(lock)
		, Object(&obj)
	{
		if (Lock == nullptr)
		{
			Object = nullptr;
		}
	}

	public:
	static ContainerAccessTypeGuard	TakeLock(ContainerLock & lock, TypeObject & obj)
	{
		return ContainerAccessTypeGuard(lock, obj);
	}
	static ContainerAccessTypeGuard MakeLock(ContainerLock & lock, TypeObject & obj)
	{
		lock.AccessL();
		return ContainerAccessTypeGuard(lock, obj);
	}
	static ContainerAccessTypeGuard TryLock(ContainerLock & lock, TypeObject & obj)
	{
		if (lock.AccessT())
		{
			return ContainerAccessTypeGuard(lock, obj);
		}
		return ContainerAccessTypeGuard();
	}

	public:
	ContainerAssignTypeGuard<TypeObject> ToAssign()
	{
		if (Count != nullptr)
		{
			if ((*Count) == 0)
			{
				delete Count;
				Count = nullptr;
				if (Lock != nullptr)
				{
					ContainerLock * lock = Lock;
					TypeObject * obj = Object;
					Lock = nullptr;
					Object = nullptr;
					lock -> AccessToAssign();
					return ContainerAssignTypeGuard<TypeObject>::TakeLock(*lock, *obj);
				}
			}
			else
			{
				(*Count)--;
			}
		}
		return ContainerAssignTypeGuard<TypeObject>();
	}
};

#endif
#include "ContainerLock/AssignGuard.hpp"
#include "ContainerLock/Lock.hpp"



bool ContainerAssignGuard::Is() const { return (Lock != nullptr); }

ContainerAssignGuard::~ContainerAssignGuard()
{
	if (Count != nullptr)
	{
		if ((*Count) == 0)
		{
			delete Count;
			if (Lock != nullptr)
			{
				Lock -> AssignU();
			}
		}
		else
		{
			(*Count)--;
		}
	}
}
ContainerAssignGuard::ContainerAssignGuard()
	: Count(nullptr)
	, Lock(nullptr)
{ }
ContainerAssignGuard::ContainerAssignGuard(const ContainerAssignGuard & other)
	: Count(other.Count)
	, Lock(other.Lock)
{
	if (Count != nullptr)
	{
		(*Count)++;
	}
}
ContainerAssignGuard & ContainerAssignGuard::operator=(const ContainerAssignGuard & other)
{
	if (Count != nullptr)
	{
		if ((*Count) == 0)
		{
			delete Count;
			if (Lock != nullptr)
			{
				Lock -> AssignU();
			}
		}
		else
		{
			(*Count)--;
		}
	}

	Count = other.Count;
	Lock = other.Lock;
	if (Count != nullptr)
	{
		(*Count)++;
	}

	return *this;
}

ContainerAssignGuard::ContainerAssignGuard(ContainerLock & lock)
	: Count(new unsigned)
	, Lock(&lock)
{
	if (Lock != nullptr)
	{
		(*Count) = 0;
	}
	else
	{
		delete Count;
		Count = nullptr;
	}
}

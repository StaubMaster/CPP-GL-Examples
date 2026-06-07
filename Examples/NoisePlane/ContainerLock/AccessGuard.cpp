#include "ContainerLock/AccessGuard.hpp"
#include "ContainerLock/Lock.hpp"



bool ContainerAccessGuard::Is() const { return (Lock != nullptr); }

ContainerAccessGuard::~ContainerAccessGuard()
{
	if (Count != nullptr)
	{
		if ((*Count) == 0)
		{
			delete Count;
			if (Lock != nullptr)
			{
				Lock -> AccessU();
			}
		}
		else
		{
			(*Count)--;
		}
	}
}
ContainerAccessGuard::ContainerAccessGuard()
	: Count(nullptr)
	, Lock(nullptr)
{ }
ContainerAccessGuard::ContainerAccessGuard(const ContainerAccessGuard & other)
	: Count(other.Count)
	, Lock(other.Lock)
{
	if (Count != nullptr)
	{
		(*Count)++;
	}
}
ContainerAccessGuard & ContainerAccessGuard::operator=(const ContainerAccessGuard & other)
{
	if (Count != nullptr)
	{
		if ((*Count) == 0)
		{
			delete Count;
			if (Lock != nullptr)
			{
				Lock -> AccessU();
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

ContainerAccessGuard::ContainerAccessGuard(ContainerLock & lock)
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

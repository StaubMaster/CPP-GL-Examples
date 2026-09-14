#include "Threading/ObjectAssignSharedGuard.hpp"
#include "Threading/ObjectLock.hpp"



bool ObjectAssignSharedGuard::Is() const
{
	return (Lock != nullptr);
}



void ObjectAssignSharedGuard::mGive()
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
void ObjectAssignSharedGuard::mTake(ObjectLock & lock)
{
	Lock = &lock;
	Count = new unsigned(0);
}
void ObjectAssignSharedGuard::mMake(ObjectLock & lock)
{
	lock.AssignL();
	mTake(lock);
}
void ObjectAssignSharedGuard::mShare(const ObjectAssignSharedGuard & other)
{
	Count = other.Count;
	Lock = other.Lock;
	if (Count != nullptr)
	{
		(*Count)++;
	}
}



ObjectAssignSharedGuard::~ObjectAssignSharedGuard()
{
	mGive();
}
ObjectAssignSharedGuard::ObjectAssignSharedGuard()
{ }
ObjectAssignSharedGuard::ObjectAssignSharedGuard(const ObjectAssignSharedGuard & other)
{
	mShare(other);
}
ObjectAssignSharedGuard & ObjectAssignSharedGuard::operator=(const ObjectAssignSharedGuard & other)
{
	mGive();
	mShare(other);
	return *this;
}

#include "Threading/ObjectAccessSharedGuard.hpp"
#include "Threading/ObjectAccessUniqueGuard.hpp"
#include "Threading/ObjectLock.hpp"



bool ObjectAccessSharedGuard::Is() const
{
	return (Lock != nullptr);
}



void ObjectAccessSharedGuard::mGive()
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
void ObjectAccessSharedGuard::mTake(ObjectLock & lock)
{
	Lock = &lock;
	Count = new unsigned(0);
}
void ObjectAccessSharedGuard::mMake(ObjectLock & lock)
{
	lock.AccessL();
	mTake(lock);
}
void ObjectAccessSharedGuard::mShare(const ObjectAccessSharedGuard & other)
{
	Lock = other.Lock;
	Count = other.Count;
	if (Count != nullptr)
	{
		(*Count)++;
	}
}

void ObjectAccessSharedGuard::mShare(ObjectAccessUniqueGuard & other)
{
	mGive();
	if (other.Lock != nullptr)
	{
		mTake(*other.Lock);
		other.Lock = nullptr;
	}
}



ObjectAccessSharedGuard::~ObjectAccessSharedGuard()
{
	mGive();
}
ObjectAccessSharedGuard::ObjectAccessSharedGuard()
{ }
ObjectAccessSharedGuard::ObjectAccessSharedGuard(const ObjectAccessSharedGuard & other)
{
	mShare(other);
}
ObjectAccessSharedGuard & ObjectAccessSharedGuard::operator=(const ObjectAccessSharedGuard & other)
{
	mGive();
	mShare(other);
	return *this;
}

#include "Threading/Guard/Access/Unique.hpp"
#include "Threading/Lock.hpp"



bool ObjectAccessUniqueGuard::Is() const
{
	return (Lock != nullptr);
}



void ObjectAccessUniqueGuard::mGive()
{
	if (Lock != nullptr)
	{
		Lock -> AccessU();
	}
}
void ObjectAccessUniqueGuard::mTake(ObjectLock & lock)
{
	Lock = &lock;
}
void ObjectAccessUniqueGuard::mMake(ObjectLock & lock)
{
	lock.AccessL();
	mTake(lock);
}



ObjectAccessUniqueGuard::~ObjectAccessUniqueGuard()
{
	mGive();
}
ObjectAccessUniqueGuard::ObjectAccessUniqueGuard()
{ }

ObjectAccessUniqueGuard::ObjectAccessUniqueGuard(ObjectAccessUniqueGuard && other)
{
	Lock = other.Lock;
	other.Lock = nullptr;
}
ObjectAccessUniqueGuard & ObjectAccessUniqueGuard::operator=(ObjectAccessUniqueGuard && other)
{
	mGive();
	Lock = other.Lock;
	other.Lock = nullptr;
	return *this;
}

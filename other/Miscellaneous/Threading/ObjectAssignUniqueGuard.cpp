#include "Threading/ObjectAssignUniqueGuard.hpp"
#include "Threading/ObjectLock.hpp"



bool ObjectAssignUniqueGuard::Is() const
{
	return (Lock != nullptr);
}



void ObjectAssignUniqueGuard::mGive()
{
	if (Lock != nullptr)
	{
		Lock -> AssignU();
	}
}
void ObjectAssignUniqueGuard::mTake(ObjectLock & lock)
{
	Lock = &lock;
}
void ObjectAssignUniqueGuard::mMake(ObjectLock & lock)
{
	lock.AssignL();
	mTake(lock);
}



ObjectAssignUniqueGuard::~ObjectAssignUniqueGuard()
{
	mGive();
}
ObjectAssignUniqueGuard::ObjectAssignUniqueGuard()
{ }

ObjectAssignUniqueGuard::ObjectAssignUniqueGuard(ObjectAssignUniqueGuard && other)
{
	Lock = other.Lock;
	other.Lock = nullptr;
}
ObjectAssignUniqueGuard & ObjectAssignUniqueGuard::operator=(ObjectAssignUniqueGuard && other)
{
	mGive();
	Lock = other.Lock;
	other.Lock = nullptr;
	return *this;
}

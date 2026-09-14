#ifndef  OBJECT_TYPE_ASSIGN_SHARED_GUARD_HPP
# define OBJECT_TYPE_ASSIGN_SHARED_GUARD_HPP

# include "Threading/ObjectAssignSharedGuard.hpp"
# include "Threading/ObjectLock.hpp"

template<typename TypeObject> struct ObjectTypeAssignSharedGuard : public ObjectAssignSharedGuard
{
	private:
	TypeObject *	Object = nullptr;

	public:
	TypeObject & operator*() { return (*Object); }

	private: public:
	void	mTake(ObjectLock & lock, TypeObject & obj)
	{
		ObjectAssignSharedGuard::mTake(lock);
		Object = &obj;
	}
	void	mMake(ObjectLock & lock, TypeObject & obj)
	{
		ObjectAssignSharedGuard::mMake(lock);
		Object = &obj;
	}

	public:
	~ObjectTypeAssignSharedGuard() = default;
	ObjectTypeAssignSharedGuard() = default;
	ObjectTypeAssignSharedGuard(const ObjectTypeAssignSharedGuard & other) = default;
	ObjectTypeAssignSharedGuard & operator=(const ObjectTypeAssignSharedGuard & other) = default;

	public:
	static ObjectTypeAssignSharedGuard	Take(ObjectLock & lock, TypeObject & obj)
	{
		ObjectTypeAssignSharedGuard guard;
		guard.mTake(lock, obj);
		//guard.mTake(lock);
		//guard.Object = &obj;
		return guard;
		//return ObjectTypeAssignSharedGuard(lock, obj);
	}
	static ObjectTypeAssignSharedGuard	Make(ObjectLock & lock, TypeObject & obj)
	{
		ObjectTypeAssignSharedGuard guard;
		guard.mMake(lock, obj);
		//guard.mMake(lock);
		//guard.Object = &obj;
		return guard;
		//lock.AssignL();
		//return ObjectTypeAssignSharedGuard(lock, obj);
	}
	/*static ObjectTypeAssignSharedGuard	TryLock(ObjectLock & lock, TypeObject & obj)
	{
		if (lock.AssignT())
		{
			return ObjectTypeAssignSharedGuard(lock, obj);
		}
		return ObjectTypeAssignSharedGuard();
	}*/
};

#endif
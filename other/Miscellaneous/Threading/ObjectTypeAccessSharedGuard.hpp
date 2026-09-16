#ifndef  OBJECT_TYPE_ACCESS_GUARD_HPP
# define OBJECT_TYPE_ACCESS_GUARD_HPP

# include "Threading/ObjectAccessSharedGuard.hpp"
# include "Threading/ObjectLock.hpp"

template<typename TypeObject> struct ObjectTypeAssignSharedGuard;
template<typename TypeObject> struct ObjectTypeAccessUniqueGuard;

template<typename TypeObject> struct ObjectTypeAccessSharedGuard : public ObjectAccessSharedGuard
{
	private: public:
	TypeObject *	Object = nullptr;

	public:
	const TypeObject & operator*() const { return (*Object); }

	private: public:
	void	mTake(ObjectLock & lock, TypeObject & obj)
	{
		ObjectAccessSharedGuard::mTake(lock);
		Object = &obj;
	}
	void	mMake(ObjectLock & lock, TypeObject & obj)
	{
		ObjectAccessSharedGuard::mMake(lock);
		Object = &obj;
	}
	void	mShare(ObjectTypeAccessUniqueGuard<TypeObject> & other)
	{
		ObjectAccessSharedGuard::mShare(other);
		Object = other.Object;
		other.Object = nullptr;
	}

	public:
	~ObjectTypeAccessSharedGuard() = default;
	ObjectTypeAccessSharedGuard() = default;
	ObjectTypeAccessSharedGuard(const ObjectTypeAccessSharedGuard & other) = default;
	ObjectTypeAccessSharedGuard & operator=(const ObjectTypeAccessSharedGuard & other) = default;

	protected:
	ObjectTypeAccessSharedGuard(ObjectLock & lock, TypeObject & obj)
		: ObjectAccessSharedGuard(lock)
		, Object(&obj)
	{
		if (Lock == nullptr)
		{
			Object = nullptr;
		}
	}

	public:
	static ObjectTypeAccessSharedGuard	Take(ObjectLock & lock, TypeObject & obj)
	{
		ObjectTypeAccessSharedGuard guard;
		guard.mTake(lock, obj);
		return guard;
	}
	static ObjectTypeAccessSharedGuard	Make(ObjectLock & lock, TypeObject & obj)
	{
		ObjectTypeAccessSharedGuard guard;
		guard.mMake(lock, obj);
		return guard;
	}
	/*static ObjectTypeAccessSharedGuard	Try(ObjectLock & lock, TypeObject & obj)
	{
		ObjectTypeAccessSharedGuard guard;
		if (lock.AccessT())
		{
			guard.mTake(lock);
			guard.Object = &obj;
		}
		return guard;
	}*/

	public:
	ObjectTypeAssignSharedGuard<TypeObject>	ToAssign()
	{
		ObjectTypeAssignSharedGuard<TypeObject> guard;
		if (Count != nullptr)
		{
			if ((*Count) == 0)
			{
				delete Count;
				Count = nullptr;
				if (Lock != nullptr)
				{
					ObjectLock * lock = Lock;
					TypeObject * obj = Object;
					guard.mTake(*lock, *obj);
					Lock = nullptr;
					Object = nullptr;
					lock -> AccessToAssign();
				}
			}
			else
			{
				(*Count)--;
			}
		}
		return guard;
	}
};

#endif
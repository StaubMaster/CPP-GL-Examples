#ifndef  OBJECT_TYPE_ASSIGN_UNIQUE_GUARD_HPP
# define OBJECT_TYPE_ASSIGN_UNIQUE_GUARD_HPP

# include "Threading/ObjectAssignUniqueGuard.hpp"
# include "Threading/ObjectLock.hpp"

template<typename TypeObject> struct ObjectTypeAssignUniqueGuard : public ObjectAssignUniqueGuard
{
	private: public:
	TypeObject *	Object = nullptr;

	public:
	TypeObject & operator*() { return (*Object); }

	private: public:
	void	mTake(ObjectLock & lock, TypeObject & obj)
	{
		ObjectAssignUniqueGuard::mTake(lock);
		Object = &obj;
	}
	void	mMake(ObjectLock & lock, TypeObject & obj)
	{
		ObjectAssignUniqueGuard::mMake(lock);
		Object = &obj;
	}

	public:
	~ObjectTypeAssignUniqueGuard() = default;
	ObjectTypeAssignUniqueGuard() = default;

	ObjectTypeAssignUniqueGuard(const ObjectTypeAssignUniqueGuard & other) = delete;
	ObjectTypeAssignUniqueGuard & operator=(const ObjectTypeAssignUniqueGuard & other) = delete;

	ObjectTypeAssignUniqueGuard(ObjectTypeAssignUniqueGuard && other)
	{
		{
			Lock = other.Lock;
			Object = other.Object;
			other.Lock = nullptr;
		}
		other.Object = nullptr;
	}
	ObjectTypeAssignUniqueGuard & operator=(ObjectTypeAssignUniqueGuard && other)
	{
		{
			mGive();
			Lock = other.Lock;
			other.Lock = nullptr;
		}
		Object = other.Object;
		other.Object = nullptr;
		return *this;
	}

	public:
	static ObjectTypeAssignUniqueGuard	Take(ObjectLock & lock, TypeObject & obj)
	{
		ObjectTypeAssignUniqueGuard guard;
		guard.mTake(lock, obj);
		return guard;
	}
	static ObjectTypeAssignUniqueGuard	Make(ObjectLock & lock, TypeObject & obj)
	{
		ObjectTypeAssignUniqueGuard guard;
		guard.mMake(lock, obj);
		return guard;
	}

	public:
	/*ObjectTypeAssignSharedGuard<TypeObject>		ToShared()
	{
		ObjectTypeAssignSharedGuard<TypeObject> guard;
		guard.mShare(*this);
		guard.Object = Object;
		Object = nullptr;
		return guard;
	}*/
};

#endif
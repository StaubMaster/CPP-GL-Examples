#ifndef  OBJECT_TYPE_LOCK_HPP
# define OBJECT_TYPE_LOCK_HPP

# include "ObjectLock.hpp"

//template<typename TypeObject> struct ObjectTypeAssignGuard;
//template<typename TypeObject> struct ObjectTypeAccessGuard;

# include "ObjectTypeAccessGuard.hpp"
# include "ObjectTypeAssignGuard.hpp"

template<typename TypeObject>
struct ObjectTypeLock : public ObjectLock
{
	private:
	TypeObject &	Object;

	public:
	~ObjectTypeLock()
	{ }
	ObjectTypeLock() = delete;
	ObjectTypeLock(const ObjectTypeLock & other) = delete;
	ObjectTypeLock & operator=(const ObjectTypeLock & other) = delete;
	
	public:
	ObjectTypeLock(TypeObject & obj)
		: Object(obj)
	{ }

	public:
	ObjectTypeAccessGuard<TypeObject>	ToAccessTake()	{ return ObjectTypeAccessGuard<TypeObject>::TakeLock(*this, Object); }
	ObjectTypeAccessGuard<TypeObject>	ToAccessMake()	{ return ObjectTypeAccessGuard<TypeObject>::MakeLock(*this, Object); }
	ObjectTypeAccessGuard<TypeObject>	ToAccessTry()	{ return ObjectTypeAccessGuard<TypeObject>::TryLock(*this, Object); }

	public:
	ObjectTypeAssignGuard<TypeObject>	ToAssignTake()	{ return ObjectTypeAssignGuard<TypeObject>::TakeLock(*this, Object); }
	ObjectTypeAssignGuard<TypeObject>	ToAssignMake()	{ return ObjectTypeAssignGuard<TypeObject>::MakeLock(*this, Object); }
	ObjectTypeAssignGuard<TypeObject>	ToAssignTry()	{ return ObjectTypeAssignGuard<TypeObject>::TryLock(*this, Object); }
};

#endif
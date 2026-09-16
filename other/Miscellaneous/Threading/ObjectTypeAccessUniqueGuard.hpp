#ifndef  OBJECT_TYPE_ACCESS_UNIQUE_GUARD_HPP
# define OBJECT_TYPE_ACCESS_UNIQUE_GUARD_HPP

# include "Threading/ObjectAccessUniqueGuard.hpp"
# include "Threading/ObjectLock.hpp"

template<typename TypeObject> struct ObjectTypeAssignUniqueGuard;
template<typename TypeObject> struct ObjectTypeAccessSharedGuard;

template<typename TypeObject> struct ObjectTypeAccessUniqueGuard : public ObjectAccessUniqueGuard
{
	private: public:
	TypeObject *	Object = nullptr;

	public:
	const TypeObject & operator*() const { return (*Object); }

	private:
	void	mTake(ObjectLock & lock, TypeObject & obj)
	{
		ObjectAccessUniqueGuard::mTake(lock);
		Object = &obj;
	}
	void	mMake(ObjectLock & lock, TypeObject & obj)
	{
		ObjectAccessUniqueGuard::mMake(lock);
		Object = &obj;
	}

	public:
	~ObjectTypeAccessUniqueGuard() = default;
	ObjectTypeAccessUniqueGuard() = default;

	ObjectTypeAccessUniqueGuard(const ObjectTypeAccessUniqueGuard & other) = delete;
	ObjectTypeAccessUniqueGuard & operator=(const ObjectTypeAccessUniqueGuard & other) = delete;

	ObjectTypeAccessUniqueGuard(ObjectTypeAccessUniqueGuard && other)
		//: ObjectAccessUniqueGuard((ObjectAccessUniqueGuard &&)other)
		//, Object(other.Object)
	{
		{
			Lock = other.Lock;
			Object = other.Object;
			other.Lock = nullptr;
		}
		other.Object = nullptr;
	}
	ObjectTypeAccessUniqueGuard & operator=(ObjectTypeAccessUniqueGuard && other)
	{
		//ObjectAccessUniqueGuard::operator=((ObjectAccessUniqueGuard &&)other);
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
	void	Transfer(ObjectTypeAccessUniqueGuard & other)
	{
		{
			mGive();
			Lock = other.Lock;
			other.Lock = nullptr;
		}
		Object = other.Object;
		other.Object = nullptr;
	}

	public:
	static ObjectTypeAccessUniqueGuard	Take(ObjectLock & lock, TypeObject & obj)
	{
		ObjectTypeAccessUniqueGuard guard;
		guard.mTake(lock, obj);
		return guard;
	}
	static ObjectTypeAccessUniqueGuard	Make(ObjectLock & lock, TypeObject & obj)
	{
		ObjectTypeAccessUniqueGuard guard;
		guard.mMake(lock, obj);
		return guard;
	}

	public:
	ObjectTypeAccessSharedGuard<TypeObject>		ToShared()
	{
		ObjectTypeAccessSharedGuard<TypeObject> guard;
		guard.mShare(*this);
		guard.Object = Object;
		Object = nullptr;
		return guard;
	}

	public:
	ObjectTypeAssignUniqueGuard<TypeObject>	ToAssign()
	{
		ObjectTypeAssignUniqueGuard<TypeObject> guard;
		if (Lock != nullptr)
		{
			ObjectLock * lock = Lock;
			TypeObject * obj = Object;
			guard.mTake(*lock, *obj);
			Lock = nullptr;
			Object = nullptr;
			lock -> AccessToAssign();
		}
		return guard;
	}
};

#endif
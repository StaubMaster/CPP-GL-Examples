#ifndef  GUARD_SHARED_OBJECT_ACCESS_HPP
# define GUARD_SHARED_OBJECT_ACCESS_HPP

struct ObjectLock;
struct ObjectAccessUniqueGuard;

struct ObjectAccessSharedGuard
{
	protected: public:
	ObjectLock *	Lock = nullptr;
	unsigned int *	Count = nullptr;

	public:
	bool	Is() const;

	protected: public:
	void	mGive();
	void	mTake(ObjectLock & lock);
	void	mMake(ObjectLock & lock);
	void	mShare(const ObjectAccessSharedGuard & other);

	public:
	void	mShare(ObjectAccessUniqueGuard & other);

	public:
	~ObjectAccessSharedGuard();
	ObjectAccessSharedGuard();
	ObjectAccessSharedGuard(const ObjectAccessSharedGuard & other);
	ObjectAccessSharedGuard & operator=(const ObjectAccessSharedGuard & other);
};

#endif
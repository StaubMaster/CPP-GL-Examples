#ifndef  GUARD_SHARED_OBJECT_ASSIGN_HPP
# define GUARD_SHARED_OBJECT_ASSIGN_HPP

struct ObjectLock;

struct ObjectAssignSharedGuard
{
	protected:
	unsigned int *	Count = nullptr;
	ObjectLock *	Lock = nullptr;

	public:
	bool	Is() const;

	private: protected:
	void	mGive();
	void	mTake(ObjectLock & lock);
	void	mMake(ObjectLock & lock);
	void	mShare(const ObjectAssignSharedGuard & other);

	public:
	~ObjectAssignSharedGuard();
	ObjectAssignSharedGuard();
	ObjectAssignSharedGuard(const ObjectAssignSharedGuard & other);
	ObjectAssignSharedGuard & operator=(const ObjectAssignSharedGuard & other);
};

#endif
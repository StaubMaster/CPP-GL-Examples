#ifndef  GUARD_UNIQUE_OBJECT_ASSIGN_HPP
# define GUARD_UNIQUE_OBJECT_ASSIGN_HPP

struct ObjectLock;

struct ObjectAssignUniqueGuard
{
	protected: public:
	ObjectLock *	Lock = nullptr;

	public:
	bool	Is() const;

	protected: public:
	void	mGive();
	void	mTake(ObjectLock & lock);
	void	mMake(ObjectLock & lock);

	public:
	~ObjectAssignUniqueGuard();
	ObjectAssignUniqueGuard();

	ObjectAssignUniqueGuard(const ObjectAssignUniqueGuard & other) = delete;
	ObjectAssignUniqueGuard & operator=(const ObjectAssignUniqueGuard & other) = delete;

	protected:
	ObjectAssignUniqueGuard(ObjectAssignUniqueGuard && other);
	ObjectAssignUniqueGuard & operator=(ObjectAssignUniqueGuard && other);
};

#endif
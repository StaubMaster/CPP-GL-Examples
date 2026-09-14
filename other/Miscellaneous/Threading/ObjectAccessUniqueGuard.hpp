#ifndef  OBJECT_ACCESS_UNIQUE_GUARD_HPP
# define OBJECT_ACCESS_UNIQUE_GUARD_HPP

struct ObjectLock;

struct ObjectAccessUniqueGuard
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
	~ObjectAccessUniqueGuard();
	ObjectAccessUniqueGuard();

	ObjectAccessUniqueGuard(const ObjectAccessUniqueGuard & other) = delete;
	ObjectAccessUniqueGuard & operator=(const ObjectAccessUniqueGuard & other) = delete;

	protected:
	ObjectAccessUniqueGuard(ObjectAccessUniqueGuard && other);
	ObjectAccessUniqueGuard & operator=(ObjectAccessUniqueGuard && other);
};

#endif
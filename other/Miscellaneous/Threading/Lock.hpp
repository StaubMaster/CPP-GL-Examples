#ifndef  OBJECT_LOCK_HPP
# define OBJECT_LOCK_HPP

# include <mutex>
# include <atomic>

class StopWatch;
struct WaitDoTime;

struct ObjectLock
{
	private:
	std::atomic<unsigned int>	UseCount;
	std::mutex					AssignMutex;
	std::mutex					AccessMutex;
	std::atomic<unsigned int>	AccessCount;

	public:
	bool	InUse() const;

	public:
	~ObjectLock();
	ObjectLock();
	ObjectLock(const ObjectLock & other) = delete;
	ObjectLock & operator=(const ObjectLock & other) = delete;

	public:
	void	AccessL(); // Take (lock)
	void	AccessU(); // Give (unlock)
	bool	AccessT(); // Try

	void	AssignL(); // Take (lock)
	void	AssignU(); // Give (unlock)
	bool	AssignT(); // Try

	void	AccessToAssign();

	public:
	void	AccessL(StopWatch & watch, WaitDoTime & time);
	void	AccessU(StopWatch & watch, WaitDoTime & time);
	void	AssignL(StopWatch & watch, WaitDoTime & time);
	void	AssignU(StopWatch & watch, WaitDoTime & time);
};

#endif
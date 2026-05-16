#ifndef  CONTAINER_LOCK_HPP
# define CONTAINER_LOCK_HPP

# include <mutex>
# include <atomic>

# include "Telemetry/WaitDoTime.hpp"
# include "Telemetry/StopWatch.hpp"

struct ContainerLock
{
	/* Container Mutex
		when you want to change Container Memory
		Inserting/Removing
	*/
	/* Item Mutex
		when you want to access Items
		this prevents Container Memory from changing
		Items can still be changed by multiple Threads
	*/

	private:
	std::mutex					ContainerMutex;	// ContainerMutex
	std::mutex					ItemMutex;		// ItemAccessMutex
	std::atomic<unsigned int>	ItemLockCount;	// ItemAccessCount

	public:
	unsigned int	Count() const;

	public:
	~ContainerLock();
	ContainerLock();

	ContainerLock(const ContainerLock & other) = delete;
	ContainerLock & operator=(const ContainerLock & other) = delete;

	public:
	void	LockItems();
	void	UnLockItems();
	void	LockContainer();
	void	UnlockContainer();

	public:
	void	LockItems(StopWatch & watch, WaitDoTime & time);
	void	UnLockItems(StopWatch & watch, WaitDoTime & time);
	void	LockContainer(StopWatch & watch, WaitDoTime & time);
	void	UnlockContainer(StopWatch & watch, WaitDoTime & time);

	public:
	/*struct Object
	{
		private:
		ContainerLock &		Lock;
		bool				IsLocked;
		//

		public:
		~Object();
		Object() = delete;
		Object(ContainerLock & lock);
		Object(const Object & other);
		Object & operator=(const Object & other) = delete;
		void	Dispose();
	};*/
};

#endif
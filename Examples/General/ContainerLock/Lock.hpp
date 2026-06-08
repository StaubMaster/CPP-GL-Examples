#ifndef  CONTAINER_LOCK_HPP
# define CONTAINER_LOCK_HPP

# include <mutex>
# include <atomic>

# include "General/Telemetry/WaitDoTime.hpp"
# include "General/Telemetry/StopWatch.hpp"

struct ContainerLock
{
	private:
	std::atomic<unsigned int>	UseCount;
	std::mutex					AssignMutex;
	std::mutex					AccessMutex;
	std::atomic<unsigned int>	AccessCount;

	public:
	bool	InUse() const;

	public:
	~ContainerLock();
	ContainerLock();

	ContainerLock(const ContainerLock & other) = delete;
	ContainerLock & operator=(const ContainerLock & other) = delete;

	public:
	void	AccessL();
	void	AccessU();

	bool	AccessT();
	void	AccessToAssign();

	void	AssignL();
	void	AssignU();

	public:
	void	AccessL(StopWatch & watch, WaitDoTime & time);
	void	AccessU(StopWatch & watch, WaitDoTime & time);
	void	AssignL(StopWatch & watch, WaitDoTime & time);
	void	AssignU(StopWatch & watch, WaitDoTime & time);
};

#endif
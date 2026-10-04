#ifndef  AUX_THREAD_1_HPP
# define AUX_THREAD_1_HPP

# include "IdleLoopThread.hpp"
# include "Telemetry/WaitDoTime.hpp"

# include <mutex>
# include <condition_variable>

# include "Generics/Container/Binary.hpp"

struct ChunkContainer;
struct Chunk;

# include "3D/ChunkGuards.hpp"

# include "Telemetry/StopWatch.hpp"
# include "Threading/ObjectTypeAccessUniqueGuard.hpp"
# include "Threading/ObjectTypeAssignUniqueGuard.hpp"

// BufferDataMakeThread
struct AuxThread1 : public IdleLoopThread
{
	ChunkContainer &	Container;

	WaitDoTime		TimeFind;
	WaitDoTime		TimeDo;

	~AuxThread1() = default;
	AuxThread1() = delete;
	AuxThread1(const AuxThread1 & other) = delete;
	AuxThread1 & operator=(const AuxThread1 & other) = delete;
	AuxThread1(ChunkContainer & container);

	AccessLockedChunk	ChunkFind;

	bool	CheckFunc() override;
	void	DoFunc() override;



	private:
	Container::Binary<Chunk *>	Queue;
	std::mutex		QueueMutex;
	public:
	unsigned int	QueueCount();
	public:
	void	QueuePut(Chunk & chunk);
	void	QueueClean();



	public:
	unsigned int	Completed = 0;
	unsigned int	RemovedNull = 0;
	unsigned int	RemovedCheck = 0;
	public:
	//void	
	private:
	AccessLockedChunk			Find();
};

#endif
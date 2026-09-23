#ifndef  AUX_THREAD_1_HPP
# define AUX_THREAD_1_HPP

# include "IdleLoopThread.hpp"
# include "Telemetry/WaitDoTime.hpp"

# include <mutex>
# include <condition_variable>

# include "Generics/Container/Binary.hpp"

struct ChunkManager;
struct Chunk;

# include "3D/ChunkGuards.hpp"

# include "Telemetry/StopWatch.hpp"
# include "Threading/ObjectTypeAccessUniqueGuard.hpp"
# include "Threading/ObjectTypeAssignUniqueGuard.hpp"

// BufferDataMakeThread
struct AuxThread1 : public IdleLoopThread
{
	ChunkManager &	Manager;

	WaitDoTime		TimeMakeBufferFind;
	WaitDoTime		TimeMakeBuffer;

	~AuxThread1() = default;
	AuxThread1() = delete;
	AuxThread1(const AuxThread1 & other) = delete;
	AuxThread1 & operator=(const AuxThread1 & other) = delete;
	AuxThread1(ChunkManager & manager);

		StopWatch sw;
		AccessLockedChunk chunk;

	bool	CheckFunc() override;
	void	DoFunc() override;



	private:
	Container::Binary<Chunk *>	Queue;
	std::mutex					QueueMutex;

	public:
	unsigned int				QueueCount();
	void						QueuePut(Chunk * chunk);



	private:
	AccessLockedChunk			Find();
};

#endif
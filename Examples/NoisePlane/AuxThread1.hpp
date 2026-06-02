#ifndef  AUX_THREAD_1_HPP
# define AUX_THREAD_1_HPP

# include "Telemetry/AuxThreadBase.hpp"
# include "Telemetry/WaitDoTime.hpp"

# include <mutex>
# include <condition_variable>

# include "Miscellaneous/Container/Binary.hpp"

struct ChunkManager;
struct Chunk;
struct AccessLockedChunk;

// BufferDataMakeThread
struct AuxThread1 : public AuxThreadBase
{
	ChunkManager &	Manager;

	WaitDoTime		TimeMakeBufferFind;
	WaitDoTime		TimeMakeBuffer;

	~AuxThread1();
	AuxThread1() = delete;
	AuxThread1(ChunkManager & manager);
	AuxThread1(const AuxThread1 & other) = delete;
	AuxThread1 & operator=(const AuxThread1 & other) = delete;

	void	Func() override;



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
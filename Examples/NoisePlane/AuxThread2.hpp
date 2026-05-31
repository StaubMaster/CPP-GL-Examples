#ifndef  AUX_THREAD_2_HPP
# define AUX_THREAD_2_HPP

# include "Telemetry/AuxThreadBase.hpp"
# include "Telemetry/WaitDoTime.hpp"

# include <mutex>
# include <condition_variable>

# include "Miscellaneous/Container/Binary.hpp"

struct ChunkManager;
struct Chunk;
struct AccessLockedChunk;

# include "CenterIndexLoop3D.hpp"
# include "Voxel/ChunkGenerationNoise.hpp"

/* make a Queue for Generating/Assambling ?
	Problem:
		I want the nearest stuff to be generated first
	Solution:
		the thing that Queues a Generation can be a CenterIndexLoop
		so the stuff nearer to the Center get generated first
		which then means that the stuff near the Center get assambled first

	Problem:
		duplicates in Queue
	Solution:
		keep the flags on weather the Chunks actually needs that done or not
		if not, just skip it

	Problem:
		what if the Center changes, a lot
		now the Center is of what was the Edge
		but the Queue is alreay filled with Chunks that area now far away
		the stuff close by should be prioratized
	Solution:
		this would require soring the distances of all Chunks
		and then using Binary insertion to insert new ones
		this would also mean recalculating Distances when Center changes
		could probably just use Manhatton distance to keep Distance simple
*/

struct AuxThread2 : public AuxThreadBase
{
	ChunkManager &	Manager;
	ChunkGenerationNoise	GenerationNoise;

	WaitDoTime		TimeGenerateFind;
	WaitDoTime		TimeGenerate;

	~AuxThread2();
	AuxThread2() = delete;
	AuxThread2(ChunkManager & manager);
	AuxThread2(const AuxThread2 & other) = delete;
	AuxThread2 & operator=(const AuxThread2 & other) = delete;

	void	Func() override;



	private:
	std::condition_variable		ConditionVar;
	std::mutex					ConditionVarMutex;

	public:
	void	Poke();



	public:	
	CenterIndexLoop3D			FindLoop;
	unsigned int				FindCandidateCount;
	private:
	AccessLockedChunk			Find();
};

#endif
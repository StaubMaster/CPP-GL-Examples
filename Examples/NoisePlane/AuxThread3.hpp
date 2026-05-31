#ifndef  AUX_THREAD_3_HPP
# define AUX_THREAD_3_HPP

# include "Telemetry/AuxThreadBase.hpp"
# include "Telemetry/WaitDoTime.hpp"

# include <mutex>
# include <condition_variable>

# include "Miscellaneous/Container/Binary.hpp"

struct ChunkManager;
struct Chunk;
struct AccessLockedChunk;

struct AuxThread3 : public AuxThreadBase
{
	ChunkManager &	Manager;

	WaitDoTime		TimeAssambleFind;
	WaitDoTime		TimeAssamble;

	~AuxThread3();
	AuxThread3() = delete;
	AuxThread3(ChunkManager & manager);
	AuxThread3(const AuxThread3 & other) = delete;
	AuxThread3 & operator=(const AuxThread3 & other) = delete;

	void	Func() override;



	private:
	std::condition_variable		ConditionVar;
	std::mutex					ConditionVarMutex;

	public:
	void	Poke();



	public:	
	unsigned int				FindCandidateCount;
	private:
	AccessLockedChunk			Find();
};

#endif
#ifndef  AUX_THREAD_3_HPP
# define AUX_THREAD_3_HPP

# include "Telemetry/AuxThreadBase.hpp"
# include "Telemetry/WaitDoTime.hpp"

# include "Miscellaneous/Container/Binary.hpp"

struct ChunkManager;
struct Chunk;
struct AccessLockedChunk;
struct StructureObject;
struct VectorI3;

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



	public:	
	unsigned int				FindCandidateCount;
	private:
	AccessLockedChunk			Find();



	private:
	void	AssambleDecoration(Chunk & chunk);
	void	AssambleDecoration(Chunk & chunk, const StructureObject & obj, const VectorI3 & offset);

};

#endif
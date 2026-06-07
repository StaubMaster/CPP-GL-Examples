#ifndef  AUX_THREAD_2_HPP
# define AUX_THREAD_2_HPP

# include "Telemetry/AuxThreadBase.hpp"
# include "Telemetry/WaitDoTime.hpp"

# include <mutex>
# include <condition_variable>

# include "Miscellaneous/Container/Binary.hpp"

struct ChunkManager;
struct Chunk;

template<typename TypeObject> struct ContainerAccessTypeGuard;
typedef ContainerAccessTypeGuard<Chunk> AccessLockedChunk;

struct Voxel;

# include "ValueType/LoopU2.hpp"
# include "ValueType/LoopU3.hpp"

# include "CenterIndexLoop/3D.hpp"
# include "Chunk/GenerationNoise.hpp"

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

// seperate generating Terrain and generating Decorations

struct AuxThread2 : public AuxThreadBase
{
	ChunkManager &			Manager;
	ChunkGenerationNoise	GenerationNoise;

	WaitDoTime		TimeGenerateFind;
	WaitDoTime		TimeGenerate;

	~AuxThread2();
	AuxThread2() = delete;
	AuxThread2(ChunkManager & manager);
	AuxThread2(const AuxThread2 & other) = delete;
	AuxThread2 & operator=(const AuxThread2 & other) = delete;

	void	Func() override;



	public:	
	CenterIndexLoop3D			FindLoop;
	unsigned int				FindCandidateCount;
	private:
	AccessLockedChunk			Find();



	private:
	void	GenerateTerrain(Chunk & chunk, const ChunkGenerationNoise & noise);
	LoopU2	Loop2;
	LoopU3	Loop3;
	struct ChunkData
	{
		VectorI3		Index;
		VectorI3		Offset;
		Array3D<Voxel>	Voxels;
		ChunkData(Chunk & chunk);
	};
	/* TerrainGenerator
		takes a Chunk
		use AbsolutePosition
		use RelativePosition
		use Y Perlin2D result
		use Perlin3D result
	*/
	private:
	void	TerrainFlat(ChunkData & data, int y_chunk, unsigned int y_voxel);
	void	TerrainPillars(ChunkData & data);
	void	TerrainPlane(ChunkData & data, const Perlin2D & noise);
	void	TerrainCaveNoodle(ChunkData & data, const Perlin3D & noise0, const Perlin3D & noise1);
	void	TerrainCaveBlob(ChunkData & data, const Perlin3D & noise);
	void	TerrainGrid(ChunkData & data);
	void	TerrainCity(ChunkData & data);



	private:
	void	GenerateDecoration(Chunk & chunk, const Perlin2D & noise2, const Perlin3D & noise3);
	/* DecorationGenerator
		takes a Chunk Neighbourhood
			not just axis, but a full cube
			MineCraft uses all around a Corner
			do I want to use all around
		use AbsolutePosition
		use RelativePosition
		use Y Perlin2D result
		use Perlin3D result
	*/
	private:
	bool	FindMinYNull(Chunk & chunk, VectorU3 & udx) const;
	void	DecorateTreesCenter(Chunk & chunk);
	void	DecorateTreesLines(Chunk & chunk);
	void	DecorateTrees(Chunk & chunk, const Perlin2D & noise);
};

#endif
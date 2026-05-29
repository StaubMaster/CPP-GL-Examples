#ifndef  CHUNK_MANAGER_HPP
# define CHUNK_MANAGER_HPP

# include "ValueGen/Perlin2D.hpp"
# include "ValueGen/Perlin3D.hpp"

# include "Graphics/Shader/Base.hpp"
# include "Graphics/ShaderLayout.hpp"
# include "Graphics/Buffer.hpp"

# include "Graphics/Main/Data.hpp"

# include "ValueType/Vector/I3.hpp"
# include "ValueType/Box/I3.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "Graphics/Texture/Array2D.hpp"

//# include "GridCast/GridCast3D.hpp"

# include "Telemetry/ValueAverager.hpp"
# include "Telemetry/StopWatch.hpp"

# include <mutex>
# include <atomic>
# include <condition_variable>

struct Voxel;
struct Chunk;
struct Chunk;
struct ChunkGenerationNoise;
struct AccessLockedChunk;
enum class AxisRel : unsigned char;

struct ChunkNeighbour;

struct Ray3D;
class PolyHedra;

struct VoxelHit;

#include <iostream>
#include "ValueType/_Show.hpp"

# include "Telemetry/WaitDoTime.hpp"
# include "ContainerLock.hpp"
# include "Miscellaneous/Container/Array3D.hpp"

# include "Graphics/MultiBufferChunkU.hpp"

struct ChunkManager
{
	public:
	static WaitDoTime	TimeInsert;
	static WaitDoTime	TimeRemove;
	static WaitDoTime	TimeUpdate;
	static WaitDoTime	TimeUpdateInsert;
	static WaitDoTime	TimeUpdateRemove;

	static WaitDoTime	TimeGraphicsCreate;
	static WaitDoTime	TimeGraphicsDelete;
	static WaitDoTime	TimeDraw;



	public:
	Texture::Array2D				Texture;
	::Shader::Base					ShaderU;
	VoxelGraphics::ShaderLayout		ShaderLayoutU;
	MultiBufferChunkU				BufferU;

	// store 2D Noise Plane. so that height values only get calculated once per XZ Coordinate

	public:
	Array3D<Chunk*>	Chunks;
	ContainerLock	ChunksLock;

	unsigned int	KnowSize;
	unsigned int	CareSize;

	void	Clear();
	void	ChangeSize(unsigned int know_size, unsigned int care_size);
	void	ChangeCenter(VectorI3 center);

	VectorI3	Center;
	BoxI3		KnowBox;
	BoxI3		CareBox;

	VectorI3	absolute(VectorU3 u) const;
	VectorU3	relative(VectorI3 i) const;

	Chunk *					FindAbsOrNull(VectorI3 idx);
	AccessLockedChunk		FindAccess(VectorI3 idx);

	private:
	public:
	Container::Binary<Chunk*>	ChunksToInsert; // do this in Chunks
	Container::Binary<Chunk*>	ChunksToRemove; // ChunkDisposal
	ContainerLock				ChunksToInsertLock;
	ContainerLock				ChunksToRemoveLock;

	public:
	void	InsertAround();
	void	RemoveAround();

	void	UpdateChunksContainer();

	void	NeighbourUpdateBufferMain(VectorI3 idx);



	public:
	~ChunkManager();
	ChunkManager();

	ChunkManager(const ChunkManager & other) = delete;
	ChunkManager & operator=(const ChunkManager & other) = delete;

	public:
	//PolyHedra *	VoxelBoxPolyHedra = nullptr;
	//PolyHedra *	ChunkBoxPolyHedra = nullptr;
	//PolyHedra *	ViewRayPolyHedra = nullptr;

	private:
	public:
	VoxelHit		HitVoxel(Ray3D ray);



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

	public:
	std::mutex					GenerateChunkMutex;
	std::condition_variable		GenerateChunkConditionVar;
	AccessLockedChunk			GenerateChunkFind();

	public:
	std::mutex					AssambleChunkMutex;
	std::condition_variable		AssambleChunkConditionVar;
	AccessLockedChunk			AssambleChunkFind();



	public:
	// put Shader /Buffer here ?

	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsUpdate();

	/* BufferUpdate
		None: no Vertex Data
		Want: requrest to make Vertex Data
		Make: make Vertex Data
		Have: requrest to put Vertex Data into Buffer
		Bind: put Vertex Data into Buffer
		Done: Vertex Data is freed
	*/

	/* Queue for making BufferData ?
		duplicates ?
		Timelime:
			new Data is requested for Chunk
			new Data is requested for Chunk
			make Data
			make Data again
		nothing changed since the first make, so doing it again wastes resources
	*/
	public:
	std::mutex					MakeBufferMutex;
	std::condition_variable		MakeBufferConditionVar;
	AccessLockedChunk			MakeBufferFind();

	public:
	Container::Binary<Chunk *>	BufferUpdateU_Queue;
	std::mutex					BufferUpdateU_Queue_Mutex;

	public:
	static ValueAverager<float>		DrawTotal;
	static ValueAverager<float>		DrawWait;
	static ValueAverager<float>		DrawTextureBind;
	static ValueAverager<float>		DrawShaderBind;
	static ValueAverager<float>		DrawUpdateBind;
	static ValueAverager<float>		DrawBufferDraw;

	public:
	void	Draw();
};

#endif
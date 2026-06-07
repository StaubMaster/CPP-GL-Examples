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

# include "Telemetry/ValueAccumulator.hpp"
# include "Telemetry/StopWatch.hpp"

# include <mutex>
# include <atomic>
# include <condition_variable>

struct Voxel;
struct Chunk;
struct Chunk;
struct ChunkGenerationNoise;

template<typename TypeObject> struct ContainerAccessTypeGuard;
typedef ContainerAccessTypeGuard<Chunk> AccessLockedChunk;

enum class AxisRel : unsigned char;

struct ChunkNeighbour;

struct Ray3D;
class PolyHedra;

struct VoxelHit;

#include <iostream>
#include "ValueType/_Show.hpp"

# include "Telemetry/WaitDoTime.hpp"
# include "ContainerLock/Lock.hpp"
# include "Miscellaneous/Container/Array3D.hpp"

# include "Graphics/MultiBufferChunkU.hpp"



# include "AuxThread/AuxThread1.hpp"
# include "AuxThread/AuxThread2.hpp"
# include "AuxThread/AuxThread3.hpp"

struct ChunkManager
{
	public:
	static WaitDoTime	TimeInsert;

	static WaitDoTime	TimeInsertNew;
	static WaitDoTime	TimeInsertPut;

	static WaitDoTime	TimeRemove;
	static WaitDoTime	TimeUpdate;
	static WaitDoTime	TimeUpdateInsert;
	static WaitDoTime	TimeUpdateRemove;

	static WaitDoTime	TimeGraphicsCreate;
	static WaitDoTime	TimeGraphicsDelete;
	static WaitDoTime	TimeDraw;



	// store 2D Noise Plane. so that height values only get calculated once per XZ Coordinate

	public:
	Array3D<Chunk*>	Chunks;
	ContainerLock	ChunksLock;

	public:
	unsigned int	KnowSize;
	unsigned int	CareSize;

	public:
	VectorI3	Center;
	BoxI3		KnowBox;
	BoxI3		CareBox;

	public:
	void	Clear();
	void	ChangeSize(unsigned int know_size, unsigned int care_size);
	void	ChangeCenter(VectorI3 center);

	VectorI3	absolute(VectorU3 u) const;
	VectorU3	relative(VectorI3 i) const;

	public:
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
	void	RemoveAround(); // returns immedeatly

	void	UpdateChunksContainer();



	public:
	~ChunkManager();
	ChunkManager();

	ChunkManager(const ChunkManager & other) = delete;
	ChunkManager & operator=(const ChunkManager & other) = delete;



	private:
	public:
	VoxelHit		HitVoxel(Ray3D ray);



	public:
	//							// DrawBufferThread
	::AuxThread1	AuxThread1;	// MakeBufferThread
	::AuxThread2	AuxThread2;
	::AuxThread3	AuxThread3;



	public:
	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();

	public:
	Texture::Array2D				Texture;
	::Shader::Base					ShaderU;
	VoxelGraphics::ShaderLayout		ShaderLayoutU;
	MultiBufferChunkU				BufferU;



	/* BufferUpdate
		None: no Vertex Data
		Want: requrest to make Vertex Data
		Make: make Vertex Data
		Have: requrest to put Vertex Data into Buffer
		Bind: put Vertex Data into Buffer
		Done: Vertex Data is freed
	*/

	struct BufferHave
	{
		public:
		Container::Binary<Chunk *>	Queue;
		std::mutex					QueueMutex;
		public:
		unsigned int				QueueCount();
		void						QueuePut(Chunk * chunk);
	};
	ChunkManager::BufferHave	BufferDataHave;

	public:
	static ValueAccumulator<float>		DrawTotal;
	static ValueAccumulator<float>		DrawWait;
	static ValueAccumulator<float>		DrawTextureBind;
	static ValueAccumulator<float>		DrawShaderBind;
	static ValueAccumulator<float>		DrawUpdateBind;
	static ValueAccumulator<float>		DrawBufferDraw;

	public:
	void	Draw();
};

#endif
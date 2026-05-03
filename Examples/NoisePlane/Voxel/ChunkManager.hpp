#ifndef  CHUNK_MANAGER_HPP
# define CHUNK_MANAGER_HPP

# include "ValueGen/Perlin2D.hpp"
# include "ValueGen/Perlin3D.hpp"

# include "Graphics/Shader.hpp"

# include "ValueType/VectorI3.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "Graphics/Texture/Array2D.hpp"

//# include "GridCast/GridCast3D.hpp"


# include "Telemetry/ValueAverager.hpp"
# include "Telemetry/StopWatch.hpp"

# include <mutex>
# include <atomic>

struct Voxel;
struct Chunk;
enum class AxisRel : unsigned char;
struct VoxelIndex;

struct Ray3D;
class PolyHedra;

struct VoxelHit
{
	AxisRel		Side;
	VectorI3	Index;
	//VoxelIndex	Index;
	VectorF3	Position;
	VectorF3	Normal;

	bool	Valid() const;
	VoxelHit();
};

#include <iostream>
#include "ValueType/_Show.hpp"

struct WaitDoTime
{
	ValueAverager<float>	DoTime;
	ValueAverager<float>	WaitTime;
	WaitDoTime();
};
std::ostream & operator<<(std::ostream & o, const WaitDoTime & obj);

struct ContainerLock
{
	std::mutex					Changing;	// changing Items
	std::mutex					Checking;	// changing Container
	std::atomic<unsigned int>	CheckingCount;

	// terrible names
	// Changing changes the Container
	//  resize, assign Items
	// Checking changes Items

	void	Checking0();
	void	Checking1();
	void	Changing0();
	void	Changing1();

	void	Checking0(StopWatch & watch, WaitDoTime & time);
	void	Checking1(StopWatch & watch, WaitDoTime & time);
	void	Changing0(StopWatch & watch, WaitDoTime & time);
	void	Changing1(StopWatch & watch, WaitDoTime & time);
};

struct ChunkManager
{
	VoxelGraphics::Shader		Shader;
	Texture::Array2D			Texture;



	Container::Binary<Chunk*>	Chunks;
	ContainerLock				ChunksLock;

	// Changing
	//  lock Changing
	//  lock Checking
	//  wait for CheckingCount == 0
	//  ... change
	//  unlock Checking
	//  unlock Changing

	// Checking
	//  lock Checking
	//  CheckingCount++
	//  unlock Checking
	//  ... checking
	//  CheckingCount--



	public:
	~ChunkManager();
	ChunkManager();

	ChunkManager(const ChunkManager & other) = delete;
	ChunkManager & operator=(const ChunkManager & other) = delete;

	PolyHedra *	VoxelBoxPolyHedra = nullptr;
	PolyHedra *	ChunkBoxPolyHedra = nullptr;
	PolyHedra *	ViewRayPolyHedra = nullptr;

	unsigned int	FindChunkUndex(Chunk * chunk);
	unsigned int	FindChunkUndex(VectorI3 idx);
	Chunk *			FindChunkOrNull(VectorI3 idx);

	VoxelIndex		FindVoxelIndex(VoxelIndex idx);
	VoxelIndex		FindVoxelIndex(VectorI3 idx);

	const Voxel *	FindVoxelOrNull(VoxelIndex idx);
	const Voxel *	FindVoxelOrNull(VectorI3 idx);

	VoxelHit		HitVoxel(Ray3D ray) const;



	bool	ClearVoxel(VoxelIndex idx, Voxel & vox);
	bool	ClearVoxel(VectorI3 idx, Voxel & vox);

	bool	PlaceVoxel(VoxelIndex idx, Voxel & vox);
	bool	PlaceVoxel(VectorI3 idx, Voxel & vox);



	static WaitDoTime	TimeInsert;
	static WaitDoTime	TimeInsertNeighbours;

	static WaitDoTime	TimeRemove;

	static WaitDoTime	TimeUpdate;
	static WaitDoTime	TimeUpdateInsert;
	static WaitDoTime	TimeUpdateChange;
	static WaitDoTime	TimeUpdateRemove;

	static WaitDoTime	TimeGenerate;
	static WaitDoTime	TimeGraphics;

	static WaitDoTime	TimeGraphicsCreate;
	static WaitDoTime	TimeGraphicsDelete;
	static WaitDoTime	TimeDraw;



	private:
	public:
	Container::Binary<Chunk*>	ChunksToInsert;
	Container::Binary<Chunk*>	ChunksToRemove;
	ContainerLock				ChunksToInsertLock;
	ContainerLock				ChunksToRemoveLock;

	public:
	void	Clear();

	void	InsertAround(VectorF3 pos, unsigned int size);
	void	RemoveAround(VectorF3 pos, unsigned int size);

	void	FindNeighbours(Chunk & chunk);
	void	NullNeighbours(Chunk & chunk);

	void	UpdateChunksContainer();



	public:
	Chunk *	FindGenerateChunk(VectorF3 pos, unsigned int size);
	void	GenerateAround(const Perlin2D & noise2, const Perlin3D & noise3, VectorF3 pos, unsigned int size, unsigned int count);



	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsUpdate();

	Chunk *	FindGraphicsUpdateChunk(VectorF3 pos);
	void	GraphicsUpdateDataAround(VectorF3 pos, unsigned int count);

	void	Draw();
};

#endif
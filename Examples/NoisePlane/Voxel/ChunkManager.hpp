#ifndef  CHUNK_MANAGER_HPP
# define CHUNK_MANAGER_HPP

# include "ValueGen/Perlin2D.hpp"
# include "ValueGen/Perlin3D.hpp"

# include "Graphics/Shader.hpp"

# include "ValueType/Vector/I3.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "Graphics/Texture/Array2D.hpp"

//# include "GridCast/GridCast3D.hpp"


# include "Telemetry/ValueAverager.hpp"
# include "Telemetry/StopWatch.hpp"

# include <mutex>
# include <atomic>

struct Voxel;
struct Chunk;
struct ChunkNeighbour;
enum class AxisRel : unsigned char;

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

# include "Telemetry/WaitDoTime.hpp"
# include "ContainerLock.hpp"
# include "Miscellaneous/Container/Array3D.hpp"

struct ChunkManager
{
	VoxelGraphics::Shader		ShaderU;
	VoxelGraphics::Shader		ShaderF;
	Texture::Array2D			Texture;



	// store 2D Noise Plane. so that height values only get calculated once per XZ Coordinate

	Array3D<Chunk*>	Chunks;
//	BoxI3			ChunksBox;
	VectorI3		Center;
	VectorI3		Corner;

	Chunk *			FindLockOrNull(VectorI3 idx);
	Chunk *			FindTryLockOrNull(VectorI3 idx);

	VectorI3	absolute(VectorU3 u) const;
	VectorU3	relative(VectorI3 i) const;

	void	ChangeChunksArraySize(unsigned int size);

	void	ChangeCenterLoopX(VectorU3 u, VectorI3 diff);
	void	ChangeCenterLoopY(VectorU3 u, VectorI3 diff);
	void	ChangeCenterLoopZ(VectorU3 u, VectorI3 diff);
	void	ChangeCenter(VectorI3 center);

//	Container::Binary<Chunk*>	Chunks;
	ContainerLock				ChunksLock;



	public:
	~ChunkManager();
	ChunkManager();

	ChunkManager(const ChunkManager & other) = delete;
	ChunkManager & operator=(const ChunkManager & other) = delete;

	public:
	PolyHedra *	VoxelBoxPolyHedra = nullptr;
	PolyHedra *	ChunkBoxPolyHedra = nullptr;
	PolyHedra *	ViewRayPolyHedra = nullptr;



	private:
	public:
	VoxelHit		HitVoxel(Ray3D ray);



	public:
	static WaitDoTime	TimeInsert;
	static WaitDoTime	TimeInsertNeighbours;

	static WaitDoTime	TimeRemove;

	static WaitDoTime	TimeUpdate;
	static WaitDoTime	TimeUpdateInsert;
	static WaitDoTime	TimeUpdateChange;
	static WaitDoTime	TimeUpdateRemove;

	static WaitDoTime	TimeGenerateFind;
	static WaitDoTime	TimeGenerate;
	static WaitDoTime	TimeBuffersFind;
	static WaitDoTime	TimeBuffers;

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

	void	UpdateChunksContainer();

	ChunkNeighbour	FindNeighbours(const Chunk & chunk) const;
//	const Chunk *	NeighbourLoopChunk(const Chunk & chunk, VectorU3 & udx, AxisRel axis);
	void			NeighbourUpdateBufferMain(VectorI3 idx);



	public:
	Chunk *	FindGenerateChunk(VectorF3 pos, unsigned int size);
	void	GenerateAround(VectorF3 pos, unsigned int size, const Perlin2D & noise2, const Perlin3D & noise3);



	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsUpdate();

	Chunk *	FindGraphicsUpdateChunk(VectorF3 pos);
	void	GraphicsUpdateDataAround(VectorF3 pos);

	void	Draw();
};

#endif
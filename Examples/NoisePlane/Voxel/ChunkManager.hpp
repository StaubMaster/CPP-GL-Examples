#ifndef  CHUNK_MANAGER_HPP
# define CHUNK_MANAGER_HPP

# include "ValueGen/Perlin2D.hpp"
# include "ValueGen/Perlin3D.hpp"

# include "Graphics/Shader.hpp"
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

struct Voxel;
struct Chunk;
struct ChunkNeighbour;
struct AccessLockedChunk;
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

class MultiBuffe_ChunkU
{
	public:
	struct Entry
	{
		MultiBuffe_ChunkU &	Buffer;
		unsigned int		Offset;
		unsigned int		Length;
		// put Array here
		// update Buffer
		//  check for Array, put Array, clear Array

		bool	IsEmpty() const;
		void	MakeEmpty();

		void	Put(const Container::Array<VoxelGraphics::MainFaceU> & data);

		~Entry();
		Entry() = delete;
		Entry(MultiBuffe_ChunkU & buffer);
		Entry(const Entry & other) = delete;
		Entry & operator=(const Entry & other) = delete;
	};

	VoxelGraphics::BufferU		Buffer;
	unsigned int				Size;

	void	NewSize(unsigned int size);

	Container::Binary<Entry*>	Entrys;
	Container::Binary<int>		Offsets;
	Container::Binary<int>		Lengths;

	bool	CheckEntry(Entry & entry);
	void	Insert(Entry & entry);
	void	Remove(Entry & entry);

	void	Draw();
};

struct ChunkManager
{
	public:
	static WaitDoTime	TimeInsert;
	static WaitDoTime	TimeRemove;
	static WaitDoTime	TimeUpdate;
	static WaitDoTime	TimeUpdateInsert;
	static WaitDoTime	TimeUpdateRemove;

	static WaitDoTime	TimeGenerateFind;
	static WaitDoTime	TimeGenerate;

	static WaitDoTime	TimeBuffersFind;
	static WaitDoTime	TimeBuffers;

	static WaitDoTime	TimeGraphicsCreate;
	static WaitDoTime	TimeGraphicsDelete;
	static WaitDoTime	TimeDraw;



	public:
	VoxelGraphics::Shader		ShaderU;
	VoxelGraphics::Shader		ShaderF;
	MultiBuffe_ChunkU			BufferU;
	VoxelGraphics::BufferF		BufferF;
	Texture::Array2D			Texture;

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

	

	void			NeighbourUpdateBufferMain(VectorI3 idx);



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
	Chunk *	FindGenerateChunk();
	void	GenerateAround(const Perlin2D & noise2, const Perlin3D & noise3);



	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsUpdate();

	AccessLockedChunk	FindGraphicsUpdateChunk();
	void				GraphicsUpdateDataAround();

	void	Draw();
};

#endif
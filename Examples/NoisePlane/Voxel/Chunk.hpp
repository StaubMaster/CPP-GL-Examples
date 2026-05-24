#ifndef  CHUNK_HPP
# define CHUNK_HPP

# define CHUNK_VALUES_PER_SIDE 32
# define CHUNK_VALUES_PER_VOLM CHUNK_VALUES_PER_SIDE * CHUNK_VALUES_PER_SIDE * CHUNK_VALUES_PER_SIDE

// 16 * 16 * 16 = 4096
// 16 * 16 * 256 = 65536
// 32 * 32 * 32 = 32768



# include "Voxel.hpp"
# include "VoxelGraphicsData.hpp"
# include "ChunkGraphicsData.hpp"

# include "Graphics/Buffer.hpp"
# include "Graphics/Main/Data.hpp"

# include "ValueType/Vector/I3.hpp"
# include "ValueType/Vector/U3.hpp"

# include "Miscellaneous/Container/Array3D.hpp"
# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Container/Array.hpp"

# include "Telemetry/ValueAverager.hpp"

# include "ContainerLock.hpp"

# include <mutex>

//struct Perlin2D;
//struct Perlin3D;
# include "ValueGen/Perlin2D.hpp"
# include "ValueGen/Perlin3D.hpp"
struct ChunkGenerationNoise
{
	Perlin2D	Plane;
	Perlin3D	Cave0;
	Perlin3D	Cave1;
	Perlin3D	Cave2;
};

struct Structure;
struct ChunkCubeNeighbour;

//struct ChunkManager;
#include "ChunkManager.hpp"

struct Chunk;

/* Chunk Changes
Access
	dosent change Voxels, dosent change BufferNew, dosent changes BufferData, basically const
Generate
	changes Voxels, changes BufferNew, dosent changes BufferData
Buffer
	dosnet change Voxel, changes BufferNew, changes BufferData
Assign
	changes Voxels, changes BufferNew, dosent changes BufferData, for user

Buffer is like Access, since it dosent change Voxels
but gets cast from (const Chunk *) to (Chunk *) to actually change things

Generate is like Assign, since it changes Voxels and then requrests a Buffer update
*/

/* LogicalData and VisualData
whenever LogicalData changes, VisualData should be updated
whenever VisualData is updated, LogicalData should not change

LogicalData can be changed from multiple places
VisualData is only changed by the function that makes VisualData

VisualData has Stages
Stage0: making BlockData
Stage1: turning BlockData into ArrayData
Stage2: putting ArrayData into Buffer

Stages 0 and 2 can happen at the same time
Stages 1 and 2 should not happen at the same time
*/

struct AccessLockedChunk
{
	private:
	unsigned int *	Count;
	Chunk *			Pointer;

	public:
	bool			Is() const;
	const Chunk &	operator*() const;

	~AccessLockedChunk();
	AccessLockedChunk();
	AccessLockedChunk(const AccessLockedChunk & other);
	AccessLockedChunk & operator=(const AccessLockedChunk & other);

	AccessLockedChunk(Chunk * chunk);
};

struct Chunk
{
	// store Neighbours
	// need to update Neighbours
	// when inserting a chunk, change pointer from null
	// when removeing a chunk, change pointer to null
	// thats it ?

	public:
	const VectorI3		Index;
	ChunkManager &		Manager; // replace this with Neighbours
	Array3D<Voxel>		Voxels;

	public:
	const Voxel &	operator[](VectorU3 udx) const;
	const Voxel *	FindVoxelOrNull(VectorU3 udx) const;



	public:
	~Chunk();
	Chunk(VectorI3 idx, ChunkManager & manager);

	Chunk() = delete;
	Chunk(const Chunk & other) = delete;
	Chunk & operator=(const Chunk & other) = delete;



	private:
	ContainerLock	Lock;
	public:
	bool	InUse() const;
	void	AccessL();
	void	AccessU();
	bool	AccessT();
	void	AccessToAssign();
	void	AssignL();
	void	AssignU();

	AccessLockedChunk	ToAccess();
	AccessLockedChunk	ToAccessTry();





	public:
	bool	IsEmpty() const;
	bool	IsNullOrEmpty() const;

	//private:
	public:
	void	MakeEmpty();
	void	MakeNull();



	public:
	bool	HitVoxel(VectorU3 udx) const;
	bool	ClearVoxel(VectorU3 udx, Voxel & vox);
	bool	PlaceVoxel(VectorU3 udx, Voxel & vox);





	public:
	bool	GenerationDone() const;
	/* Generation
		Terrain:
			different Layers ?
			just Height Map
		Note Decorations:
			put Decorations in Container
			resolve Overlaps
		Place Decorations:
			resolve Overlaps
			put Voxels
			clear Decorations that arent needed for other Chunks
		Clear Decorations:
			clear Decorations Container
		Done:
	*/

	/*
		the chunk is already done after Placing Voxels
		Clear Decorations is related to different Chunks
		maybe just delete as needed
	*/



	public:
	bool	TerrainDone;
	void	GenerateTerrain(const ChunkGenerationNoise & noise);
	/* TerrainGenerator
		takes a Chunk
		use AbsolutePosition
		use RelativePosition
		use Y Perlin2D result
		use Perlin3D result
	*/
	private:
	void	TerrainFlat(int y_chunk, unsigned int y_voxel);
	void	TerrainPillars();
	void	TerrainPlane(const Perlin2D & noise);
	void	TerrainCaveNoodle(const Perlin3D & noise0, const Perlin3D & noise1);
	void	TerrainCaveBlob(const Perlin3D & noise);
	void	TerrainGrid();
	void	TerrainCity();



	private:
	struct StructureObject
	{
		::Structure *	Structure = nullptr;
		::VectorU3		Origin;
	};
	Container::Binary<StructureObject>	Decorations;



	public:
	bool	DecorationsGenerated;
	void	GenerateDecoration(const Perlin2D & noise2, const Perlin3D & noise3);
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
	bool	FindMinYNull(VectorU3 & udx) const;
	void	DecorateTrees(const Perlin2D & noise);



	public:
	bool	DecorationsAssambled;
	void	AssambleDecoration(const ChunkCubeNeighbour & neighbours);
	private:
	void	AssambleDecoration(const StructureObject & obj, const VectorI3 & offset);





	public:
	bool	GraphicsExist;
	MultiBuffe_ChunkU::Entry	BufferU_Entry;
	VoxelGraphics::BufferF		BufferF;

	public:
	void	GraphicsCreate();
	void	GraphicsDelete();

	public:
	bool				MainBufferDataNew;
	ChunkGraphicsData	MainBufferData;
	void	GraphicsMakeData(const ChunkAxisNeighbour & neighbours);
	/* 
		BufferUMain_UpdateData clears MainBufferData
		if during this time, MainBufferData is being remade
		then MainBufferData is undefined

		Lock Array
		have another flag for turning BlockData into Array Data
	*/

	/*
		make new MainBufferData.Block
		...
		Chunk is locked as Access. so it cannot be changed
		...
		MainBufferData.Block is done
		MainBufferData.Block to MainBufferData.Array
		...
		Chunk changes
		...
		make new MainBufferData.Block
		...
		MainBufferData.Array is put into Buffer
		MainBufferData should be cleared so that less Memory is in use
		only clear Array ?
		Block should be cleard after Array has been made
		but still lock to make sture no conflict happens
	*/

	bool	BufferUMain_NewData;
	void	BufferUMain_UpdateData();
	void	UpdateU();

	bool	BufferFMain_NewData;
	bool	BufferFInst_NewData;
	void	BufferFMain_UpdateData();
	void	BufferFInst_UpdateData();
	void	DrawF();
};

#endif

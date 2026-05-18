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

struct Perlin2D;
struct Perlin3D;
struct Structure;

enum class BufferDataState : unsigned char // put into Buffer
{
	None,
	Needed,
	Ready,
};

// make this an Array3D ?
struct ChunkManager;
struct Chunk
{
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
	void	AccessL();
	void	AccessU();
	void	AssignL();
	void	AssignU();



	public:
	bool	IsEmpty() const;
	bool	IsNullOrEmpty() const;

	private:
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
	bool	DecorationsNoted;
	bool	DecorationsPlaced;
	struct StructureObject
	{
		::Structure *	Structure = nullptr;
		::VectorI3		Origin;
	};
	Container::Binary<StructureObject>	Decorations;

	/* TerrainGenerator
		takes a Chunk
		use AbsolutePosition
		use RelativePosition
		use Y Perlin2D result
		use Perlin3D result
	*/
	public:
	static float	Generation3D_Factor;
	static float	Generation3D_Comparison;
	private:
	void	TerrainPlane();
	void	TerrainPillars();
	void	TerrainPerlin(const Perlin2D & noise);
	void	TerrainPerlin(const Perlin3D & noise);
	void	TerrainGrid();
	void	TerrainCity();
	public:
	void	GenerateTerrain(const Perlin2D & noise2, const Perlin3D & noise3);

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
	void	DecorateTrees(const Perlin2D & noise);
	public:
	void	GenerateDecorationNotes(const Perlin2D & noise2, const Perlin3D & noise3);

	void	GenerateDecorationPlace();



	public:
	bool	GraphicsExist;
	VoxelGraphics::BufferU	BufferU;
	VoxelGraphics::BufferF	BufferF;

	public:
	void	GraphicsCreate();
	void	GraphicsDelete();

	public:
	BufferDataState		MainBufferState;
	ChunkGraphicsData	MainBufferData;
	void	GraphicsMakeData(const ChunkNeighbour & neighbours);
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
	bool	BufferFMain_NewData;
	void	BufferUMain_UpdateData();
	void	BufferFMain_UpdateData();

	bool	BufferUInst_NewData;
	bool	BufferFInst_NewData;
	void	BufferUInst_UpdateData();
	void	BufferFInst_UpdateData();

	bool	BufferU_AttributesBound; // split into Main and Inst ?
	bool	BufferF_AttributesBound;
	void	DrawU();
	void	DrawF();
};

/*struct AccessLockedChunk
{
	Pointer to Chunk
	bool IsNull() const

	operator[]
	GeneratonDone()
	NeedsBuffer()

	more is not needed for access?
};*/

/* access to what ?
	general external stuff
		checking Voxels
	Generation
		needs to changes
	making Buffer
		needs to access Voxels
		but also change BufferData
*/

#endif

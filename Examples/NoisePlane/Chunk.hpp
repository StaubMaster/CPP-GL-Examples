#ifndef  CHUNK_HPP
# define CHUNK_HPP

# define CHUNK_VALUES_PER_SIDE 32
# define CHUNK_VALUES_PER_VOLM CHUNK_VALUES_PER_SIDE * CHUNK_VALUES_PER_SIDE * CHUNK_VALUES_PER_SIDE

// 16 * 16 * 16 = 4096
// 16 * 16 * 256 = 65536
// 32 * 32 * 32 = 32768



# include "Voxel.hpp"
# include "Voxel/GraphicsData.hpp"
# include "Chunk/GraphicsData.hpp"

# include "Graphics/Buffer.hpp"
# include "Graphics/Main/Data.hpp"

# include "ValueType/Vector/I3.hpp"
# include "ValueType/Vector/U3.hpp"

# include "Generics/Container/Array3D.hpp"
# include "Generics/Container/Binary.hpp"
# include "Generics/Container/Array.hpp"

# include "Telemetry/ValueAccumulator.hpp"

# include "ContainerLock/Lock.hpp"

# include <mutex>

# include "Chunk/GenerationNoise.hpp"
# include "Chunk/Neighbours.hpp"

struct ChunkManager;
struct Structure;

# include "Graphics/MultiBufferChunkU.hpp"

/* Do I need Assign Lock ?

when changing
just createa a New Voxel Array and fill that with the new data
then just replace the old Voxel Array with the new one
just lock, replace, unlock
that should be done internally

Generation is currently the only one that changes

changing should not happen at the same time
so lock it for others that want to change
but also changing should not lock checking until Voxels are changed

do the same with Chunks in ChunkManager
*/

/* deleting Chunk
how to make sure Chunk is not referanced anywhere else
*/

struct Chunk;

template<typename TypeObject> struct ContainerAccessTypeGuard;
template<typename TypeObject> struct ContainerAssignTypeGuard;

typedef ContainerAccessTypeGuard<Chunk> AccessLockedChunk;
typedef ContainerAssignTypeGuard<Chunk> AssignLockedChunk;

// StructurePlacement ?
// StructureOrientation ?
struct StructureObject
{
	::Structure *	Structure = nullptr;
	::VectorU3		Origin;
};

struct Chunk
{
	public:
	const VectorI3		Index;
	ChunkManager &		Manager;
	Array3D<Voxel>		Voxels;
	ChunkNeighbour		Neighbours;

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
	AssignLockedChunk	ToAssign();
	//AssignLockedChunk	ToAssignTry();

	static AccessLockedChunk	ToAccess(Chunk * chunk);





	public:
	bool	IsEmpty() const;
	bool	IsNullOrEmpty() const;

	//private:
	public:
	void	MakeEmpty();
	void	MakeNull();



	public:
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

	public:
	Container::Binary<StructureObject>	Decorations;

	public:
	bool	DecorationsGenerated;

	public:
	bool	DecorationsAssambled;





	public:
	ChunkGraphicsData			BufferUData;
	MultiBufferChunkU::Entry	BufferUData_Entry;
	bool						BufferUData_Want;
	void						BufferUData_Make();
	bool						BufferUData_Have;
	void						BufferUData_Update();
};

#endif

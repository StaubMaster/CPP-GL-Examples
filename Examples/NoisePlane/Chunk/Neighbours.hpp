#ifndef  CHUNK_NEIGHBOURS_HPP
# define CHUNK_NEIGHBOURS_HPP

struct Chunk;
struct ChunkManager;
struct VectorU3;
struct VectorI3;
enum class AxisRel : unsigned char;
enum class VoxelType : unsigned char;

# include "Generics/Container/Array3D.hpp"

/* these are Axis Neighbours
instead store all Neighbours
so 3x3x3
store in Chunk
this is what I had before
but I removed it because findind Chunks was slow
but now I need to find them every time I want to do something

also this takes a lot of space
Chunks in Axis are 56 Bytes
3x3x3 whould be 216 Bytes

sizeof(Chunk) is currently 744
this would make it 960 Bytes

this would still be a fraction compared to Voxels and GraphicsData
so it would be fine ?
*/

/* different Neighbours

Generation
	needs 3x3x3 Neighbours
	or 2x2x2
	all besides Here should be Access locked
	Here should be Assign locked
UpdateBuffer
	needs Axis Neighbours
	all should be Access locked
	Here gets BufferDat changed
RequestBuffer Update
	when a Chunk changes from Generation or Assign
	then neighbouring Chunks need to update Visuals

	if this and UpdateBuffer change Flag at weird times
	it could cause a Chunk to not be Updated when it should be

	Request only gets set from Chunk assign
	Buffer should not be made at the same time as assign

	currently, Buffers can be made if neighbour is generated
	when the neighbour finishes, it tells it neighbouts to updat visuals
	but the neighbout is currently updating visuals
	which causes the update to be lost
*/

// this is uses specifically used for making Buffer Data
// Here isnt really used since it gets compressed into is_empty
// store is_empty here ?

/*struct ChunkAxisNeighbour
{
	private:
	const Chunk *	Here;
	const Chunk *	PrevX;
	const Chunk *	PrevY;
	const Chunk *	PrevZ;
	const Chunk *	NextX;
	const Chunk *	NextY;
	const Chunk *	NextZ;

	public:
	~ChunkAxisNeighbour();
	ChunkAxisNeighbour();
	ChunkAxisNeighbour(const ChunkAxisNeighbour & other);
	ChunkAxisNeighbour & operator=(const ChunkAxisNeighbour & other);
	ChunkAxisNeighbour(const Chunk & chunk);

	public:
	void	ChangePrevX(const Chunk * chunk);
	void	ChangePrevY(const Chunk * chunk);
	void	ChangePrevZ(const Chunk * chunk);
	void	ChangeNextX(const Chunk * chunk);
	void	ChangeNextY(const Chunk * chunk);
	void	ChangeNextZ(const Chunk * chunk);

	public:
	bool	IsVisiblePrevX(const Array3D<unsigned char> & is_empty, VectorU3 udx) const;
	bool	IsVisiblePrevY(const Array3D<unsigned char> & is_empty, VectorU3 udx) const;
	bool	IsVisiblePrevZ(const Array3D<unsigned char> & is_empty, VectorU3 udx) const;
	bool	IsVisibleNextX(const Array3D<unsigned char> & is_empty, VectorU3 udx) const;
	bool	IsVisibleNextY(const Array3D<unsigned char> & is_empty, VectorU3 udx) const;
	bool	IsVisibleNextZ(const Array3D<unsigned char> & is_empty, VectorU3 udx) const;

	public:
	bool	GenerationDone() const;
};*/

/*struct ChunkCubeNeighbour
{
	private:
	public:
	const Chunk * Cube[3][3][3];

	public:
	~ChunkCubeNeighbour();
	ChunkCubeNeighbour();
	ChunkCubeNeighbour(const ChunkCubeNeighbour & other);
	ChunkCubeNeighbour & operator=(const ChunkCubeNeighbour & other);
	ChunkCubeNeighbour(const Chunk & chunk);

	public:
	void	Change(const Chunk * chunk, unsigned int x, unsigned int y, unsigned int z);

	public:
	bool	CanAssamble() const;
};*/

struct ChunkNeighbour
{
	// [Z][Y][X]
	// [0] Prev
	// [1] Here
	// [2] Next

	private:
	public:
	Chunk * Cube[3][3][3];

	public:
	~ChunkNeighbour();
	ChunkNeighbour();
	ChunkNeighbour(const ChunkNeighbour & other);
	ChunkNeighbour & operator=(const ChunkNeighbour & other);
	ChunkNeighbour(Chunk & chunk);

	public:
	bool	IsVisiblePrevX(const Array3D<VoxelType> & voxel_types, VectorU3 udx) const;
	bool	IsVisiblePrevY(const Array3D<VoxelType> & voxel_types, VectorU3 udx) const;
	bool	IsVisiblePrevZ(const Array3D<VoxelType> & voxel_types, VectorU3 udx) const;
	bool	IsVisibleNextX(const Array3D<VoxelType> & voxel_types, VectorU3 udx) const;
	bool	IsVisibleNextY(const Array3D<VoxelType> & voxel_types, VectorU3 udx) const;
	bool	IsVisibleNextZ(const Array3D<VoxelType> & voxel_types, VectorU3 udx) const;

	public:
	void	BufferDataWant();

	public:
	bool	CanMakeBuffer() const;

	public:
	bool	CanAssamble() const;
};

#endif
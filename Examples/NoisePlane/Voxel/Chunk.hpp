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
# include "ChunkNeighbours.hpp"

# include "ValueType/VectorI3.hpp"
# include "ValueType/VectorU3.hpp"

# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Container/Array.hpp"

# include "Telemetry/ValueAverager.hpp"

# include <mutex>

struct Perlin2D;
struct Perlin3D;

// chunks area already used via Pointer
// make Voxels also a Pointer (rename to Data)
// add a Dispose Function and store everything as a non Pointer
// 
// if the Chunks is empty (all 0) delete Data

// States
// UnGenerated
// Done
//  Empty
//  Filled

// not Done:	dont draw Faces that point here
// Empty:		do draw Faces that point here

enum class GenerationState
{
	None,
	Generated,
//	Decorated,
//	Done,
};

enum class BufferDataState // put into Buffer
{
	None,
	Needed,
	Ready,
	Drawable,
};

struct Chunk
{
	public:
	const VectorI3		Index;
	ChunkNeighbours		Neighbours;
	private:
	Voxel *				Data;
	public:
	::GenerationState	GenerationState;

	private:
	std::mutex			Changing;
	public:
	void	lock();
	void	unlock();
	bool	try_lock();

	public:
	bool	Done() const;

	const Voxel &	operator[](VectorU3 udx) const;

	const Voxel *	FindVoxelOrNull(VectorU3 udx) const;

	public:
	~Chunk();
	Chunk(VectorI3 idx);

	Chunk() = delete;
	Chunk(const Chunk & other) = delete;
	Chunk & operator=(const Chunk & other) = delete;

	public:
	bool	IsEmpty() const;
	bool	IsNullOrEmpty() const;
	private:
	void	MakeEmpty();
	void	MakeNull();

	public:
	bool	ClearVoxel(VectorU3 udx, Voxel & vox);
	bool	PlaceVoxel(VectorU3 udx, Voxel & vox);
	// ChangeVoxel ?

	bool	Hit(VectorU3 udx) const;

	static float	Generation3D_Factor;
	static float	Generation3D_Comparison;

	private:
	// do these with Files
	//void	GenerateOrientation();
	void	GenerateGrid();
	void	GeneratePlane();
	void	GeneratePillars();
	void	GeneratePerlin(const Perlin2D & noise);
	void	GeneratePerlin(const Perlin3D & noise);
	public:
	void	Generate(const Perlin2D & noise2, const Perlin3D & noise3);



	VoxelGraphics::Buffer	Buffer;

	bool	GraphicsExist; // Buffer is the only thing ?
	public:
	void	GraphicsCreate();
	void	GraphicsDelete();

	bool	BufferNeedsInit; // split into Main and Inst. put into Buffer ?

	public:
	bool	Visible(VectorU3 udx, AxisRel axis) const;

	public:
	BufferDataState		MainBufferState; // put into Buffer ?
	ChunkGraphicsData	MainBufferData;
	void	GraphicsUpdateMainData();
	void	GraphicsUpdateMainBuffer();

	bool	InstBufferNeedsData;
	void	UpdateInstBuffer();

	void	Draw();
};

/*struct ChunkLock
{
	private:
	::Chunk *		Chunk;
	unsigned int *	Count;

	public:
	bool	Is() const;

	// how to access Chunk ?
	// operator* ?

	public:
	~ChunkLock(); // (count--) or (delete and unlock)
	ChunkLock(Chunk * chunk); // new count and count++ and lock chunk
	ChunkLock(const ChunkLock & other); // count++
	ChunkLock() = delete;
	ChunkLock & operator=(const ChunkLock & other) = delete;
};*/

#endif

#ifndef  CHUNK_HPP
# define CHUNK_HPP

# define CHUNK_VALUES_PER_SIDE 16
# define CHUNK_VALUES_PER_VOLM CHUNK_VALUES_PER_SIDE * CHUNK_VALUES_PER_SIDE * CHUNK_VALUES_PER_SIDE

# include "Voxel.hpp"
# include "Graphics/Buffer.hpp"
# include "Graphics/Main/Data.hpp"
# include "ChunkNeighbours.hpp"

# include "ValueType/VectorI3.hpp"
# include "ValueType/VectorU3.hpp"

#include "Miscellaneous/Container/Binary.hpp"

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

struct Chunk
{
	public:		Voxel *				Data;
	public:		VectorI3			Index;
	public:		ChunkNeighbours		Neighbours;
	public:		::GenerationState	GenerationState;

	public:
	bool	Done() const;

	Voxel &			operator[](VectorU3 udx);
	const Voxel &	operator[](VectorU3 udx) const;

	~Chunk();
	Chunk(VectorI3 idx, bool graphics_exist);
	Chunk() = delete;
	Chunk(const Chunk & other) = delete;
	Chunk & operator=(const Chunk & other) = delete;
	//void	Dispose();

	bool	IsEmpty() const;
	bool	IsNullOrEmpty() const;
	void	MakeEmpty();
	void	MakeNull();

	void	TestOrientation();
	void	TestHouse();

	static float	Generation3D_Factor;
	static float	Generation3D_Comparison;

	void	GenerateGrid();
	void	GeneratePerlin(const Perlin2D & noise);
	void	GeneratePerlin(const Perlin3D & noise);
	void	Generate(const Perlin2D & noise2, const Perlin3D & noise3);



	VoxelGraphics::Buffer	Buffer;

	bool	GraphicsExist; // Buffer is the only thing ?
	void	GraphicsCreate();
	void	GraphicsDelete();

//	void	GraphicsUpdateBuffer();
//	void	GraphicsUpdateData();

	bool	BufferNeedsInit; // split into Main and Inst. put into Buffer ?

	enum class BufferDataState // put into Buffer
	{
		None,
		Needed,
		Ready,
	};

	BufferDataState	MainBufferState; // put into Buffer ?
	Container::Binary<VoxelGraphics::MainTriangle>	MainBufferData; // put into Buffer ?
	void	GraphicsUpdateMainData();
	void	GraphicsUpdateMainBuffer();

	bool	InstBufferNeedsData;
	void	UpdateInstBuffer();

	void	Draw();
};

#endif

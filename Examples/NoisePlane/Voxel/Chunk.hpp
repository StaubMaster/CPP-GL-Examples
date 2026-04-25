#ifndef  CHUNK_HPP
# define CHUNK_HPP

# define CHUNK_VALUES_PER_SIDE 16
# define CHUNK_VALUES_PER_VOLM CHUNK_VALUES_PER_SIDE * CHUNK_VALUES_PER_SIDE * CHUNK_VALUES_PER_SIDE

# include "Voxel.hpp"
# include "Graphics/Buffer.hpp"
# include "ChunkNeighbours.hpp"

# include "ValueType/VectorI3.hpp"
# include "ValueType/VectorU3.hpp"

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
	Voxel *				Data;
	VectorI3			Index;
	ChunkNeighbours		Neighbours;
	::GenerationState	GenerationState;

	bool	Done() const;

	Voxel &			operator[](VectorU3 udx);
	const Voxel &	operator[](VectorU3 udx) const;

	~Chunk();
	Chunk();
	Chunk(const Chunk & other) = delete;
	Chunk & operator=(const Chunk & other) = delete;
	//void	Dispose();

	bool	IsEmpty() const;
	bool	IsNullOrEmpty() const;
	void	MakeEmpty();
	void	MakeNull();

	void	TestOrientation();
	void	TestHouse();

	void	GenerateGrid();
	void	GeneratePerlin(const Perlin2D & noise);
	void	GeneratePerlin(const Perlin3D & noise);
	void	Generate(const Perlin2D & noise2, const Perlin3D & noise3);



	unsigned int			MainCount;
	VoxelGraphics::Buffer	Buffer;

	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();

	bool	BufferNeedsInit;

	bool	MainBufferNeedsData;
	void	UpdateMainBuffer();

	bool	InstBufferNeedsData;
	void	UpdateInstBuffer();

	void	Draw();
};

#endif

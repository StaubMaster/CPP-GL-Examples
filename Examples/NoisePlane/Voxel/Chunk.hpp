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

// chunks area already used via Pointer
// make Voxels also a Pointer (rename to Data)
// add a Dispose Function and store everything as a non Pointer
// 
// when the Chunks is empty (all 0) delete Data

struct Chunk
{
	Voxel				Voxels[CHUNK_VALUES_PER_VOLM];
	VectorI3			Index;
	ChunkNeighbours		Neighbours;

	Voxel &			operator[](VectorU3 udx);
	const Voxel &	operator[](VectorU3 udx) const;

	~Chunk();
	Chunk();
	Chunk(const Chunk & other) = delete;
	Chunk & operator=(const Chunk & other) = delete;

	bool	IsGenerated;
	void	GenerateGrid();
	void	GeneratePerlin(const Perlin2D & noise);
	void	Generate(const Perlin2D & noise);



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

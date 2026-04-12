#ifndef  CHUNK_HPP
# define CHUNK_HPP

# define CHUNK_SCALE 0.0625

# define CHUNK_VALUES_PER_SIDE 16
# define CHUNK_VALUES_PER_VOLM CHUNK_VALUES_PER_SIDE * CHUNK_VALUES_PER_SIDE * CHUNK_VALUES_PER_SIDE

# include "ValueType/VectorI3.hpp"
# include "ValueType/VectorU3.hpp"

# include "ChunkGraphics.hpp"
//# include "ChunkNeighbours.hpp"

struct Perlin2D;

struct Chunk
{
	float				Values[CHUNK_VALUES_PER_VOLM];
	VectorI3			Index;
//	ChunkNeighbours		Neighbours;

	~Chunk();
	Chunk();
	Chunk(const Chunk & other) = delete;
	Chunk & operator=(const Chunk & other) = delete;

	bool	IsGenerated;
	void	Generate(const Perlin2D & noise);



	ChunkGraphics::Buffer	Buffer;

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

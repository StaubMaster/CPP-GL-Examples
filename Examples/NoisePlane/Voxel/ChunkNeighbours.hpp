#ifndef  CHUNK_NEIGHBOURS_HPP
# define CHUNK_NEIGHBOURS_HPP

struct VectorU3;
struct Voxel;
struct Chunk;

enum class Axis : unsigned char;

struct ChunkNeighbours
{
	Chunk *		Here;

	Chunk *		NextX;
	Chunk *		NextY;
	Chunk *		NextZ;

	Chunk *		PrevX;
	Chunk *		PrevY;
	Chunk *		PrevZ;

	~ChunkNeighbours();
	ChunkNeighbours();
	ChunkNeighbours(const ChunkNeighbours & other);
	ChunkNeighbours & operator=(const ChunkNeighbours & other);

	bool		Visible(Axis axis, VectorU3 udx) const;

	void	UpdateOthersHere();

	void	UpdateBufferMain();
};

#endif
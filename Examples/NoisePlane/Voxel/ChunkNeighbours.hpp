#ifndef  CHUNK_NEIGHBOURS_HPP
# define CHUNK_NEIGHBOURS_HPP

struct VectorU3;
struct Voxel;
struct Chunk;

enum class AxisDirection
{
	Here  = 0b000,
	PrevX = 0b001,
	PrevY = 0b010,
	PrevZ = 0b100,
	NextX = 0b110,
	NextY = 0b101,
	NextZ = 0b011,
	None  = 0b111,
};

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

	bool		Visible(AxisDirection dir, VectorU3 udx) const;

	void	UpdateOthersHere();

	void	UpdateBufferMain();
};

#endif
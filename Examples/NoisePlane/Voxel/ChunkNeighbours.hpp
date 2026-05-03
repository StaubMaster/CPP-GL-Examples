#ifndef  CHUNK_NEIGHBOURS_HPP
# define CHUNK_NEIGHBOURS_HPP

struct VectorU3;
struct Voxel;
struct Chunk;

enum class AxisRel : unsigned char;

struct ChunkNeighbours
{
	private:
	Chunk *		Here;
	Chunk *		PrevX;
	Chunk *		PrevY;
	Chunk *		PrevZ;
	Chunk *		NextX;
	Chunk *		NextY;
	Chunk *		NextZ;

	public:
	~ChunkNeighbours();
	ChunkNeighbours();
	ChunkNeighbours(const ChunkNeighbours & other);
	ChunkNeighbours & operator=(const ChunkNeighbours & other);

	public:
	const Chunk *	Loop(AxisRel axis, VectorU3 & udx) const;

	// just take a Container of Chunks
	void	Change(AxisRel axis, Chunk * chunk);

	void	UpdateBufferMain();
};

#endif
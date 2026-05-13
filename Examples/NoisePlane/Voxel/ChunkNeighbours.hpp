#ifndef  CHUNK_NEIGHBOURS_HPP
# define CHUNK_NEIGHBOURS_HPP

struct Chunk;
struct VectorU3;
enum class AxisRel : unsigned char;

struct ChunkNeighbour
{
	Chunk *		Here;
	Chunk *		PrevX;
	Chunk *		PrevY;
	Chunk *		PrevZ;
	Chunk *		NextX;
	Chunk *		NextY;
	Chunk *		NextZ;

	const Chunk *	LoopPrevX(VectorU3 & udx) const;
	const Chunk *	LoopPrevY(VectorU3 & udx) const;
	const Chunk *	LoopPrevZ(VectorU3 & udx) const;
	const Chunk *	LoopNextX(VectorU3 & udx) const;
	const Chunk *	LoopNextY(VectorU3 & udx) const;
	const Chunk *	LoopNextZ(VectorU3 & udx) const;

	const Chunk *	Loop(VectorU3 & udx, AxisRel axis) const;

	bool	Visible(VectorU3 udx, AxisRel axis) const;
};

#endif
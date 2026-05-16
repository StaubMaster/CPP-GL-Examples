#ifndef  CHUNK_NEIGHBOURS_HPP
# define CHUNK_NEIGHBOURS_HPP

struct Chunk;
struct Voxel;
struct VectorU3;
enum class AxisRel : unsigned char;

# include "Miscellaneous/Container/Array3D.hpp"

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

struct ChunkNeighbour
{
	// only Here Chunk as a referance
	// the others should be more ChunkNeigbours
	// dont make accessible directly

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
	const Chunk *	Loop(VectorU3 & udx, const AxisRel & axis) const;

	bool	IsVisiblePrevX(const Array3D<unsigned char> & is_empty, VectorU3 udx) const;
	bool	IsVisiblePrevY(const Array3D<unsigned char> & is_empty, VectorU3 udx) const;
	bool	IsVisiblePrevZ(const Array3D<unsigned char> & is_empty, VectorU3 udx) const;
	bool	IsVisibleNextX(const Array3D<unsigned char> & is_empty, VectorU3 udx) const;
	bool	IsVisibleNextY(const Array3D<unsigned char> & is_empty, VectorU3 udx) const;
	bool	IsVisibleNextZ(const Array3D<unsigned char> & is_empty, VectorU3 udx) const;
};

#endif
#ifndef  CHUNK_NEIGHBOURS_HPP
# define CHUNK_NEIGHBOURS_HPP

struct Chunk;
struct ChunkManager;
struct VectorU3;
struct VectorI3;
enum class AxisRel : unsigned char;
struct Voxel;

# include "Generics/Container/Array3D.hpp"

struct ChunkNeighbour
{
	// [Z][Y][X]
	// [0] Prev
	// [1] Here
	// [2] Next

	private:
	public:
	Chunk * Cube[3][3][3];

	public:
	~ChunkNeighbour();
	ChunkNeighbour();
	ChunkNeighbour(const ChunkNeighbour & other);
	ChunkNeighbour & operator=(const ChunkNeighbour & other);
	ChunkNeighbour(Chunk & chunk);

	public:
	bool	IsVisiblePrevX(const Array3D<bool> & voxel_is_empty, VectorU3 udx) const;
	bool	IsVisiblePrevY(const Array3D<bool> & voxel_is_empty, VectorU3 udx) const;
	bool	IsVisiblePrevZ(const Array3D<bool> & voxel_is_empty, VectorU3 udx) const;
	bool	IsVisibleNextX(const Array3D<bool> & voxel_is_empty, VectorU3 udx) const;
	bool	IsVisibleNextY(const Array3D<bool> & voxel_is_empty, VectorU3 udx) const;
	bool	IsVisibleNextZ(const Array3D<bool> & voxel_is_empty, VectorU3 udx) const;

	public:
	void	BufferDataWant();

	public:
	bool	CanMakeBuffer() const;

	public:
	bool	CanAssamble() const;
};

#endif
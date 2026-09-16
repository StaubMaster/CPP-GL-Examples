#ifndef  CHUNK_NEIGHBOURS_HPP
# define CHUNK_NEIGHBOURS_HPP

struct Chunk;
struct VectorU3;

# include "Generics/Container/Array3D.hpp"

struct ChunkNeighbour
{
	// [Z][Y][X]
	// [0] Prev
	// [1] Here
	// [2] Next

	private:
	public:
	Chunk * Cube[3][3][3] = {
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
		{
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
			{ nullptr, nullptr, nullptr },
		},
	};

	public:
	~ChunkNeighbour() = default;
	ChunkNeighbour() = default;
	ChunkNeighbour(const ChunkNeighbour & other) = default;
	ChunkNeighbour & operator=(const ChunkNeighbour & other) = default;

	ChunkNeighbour(Chunk * chunk);

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
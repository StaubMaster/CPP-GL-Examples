#ifndef  CHUNK_MANAGER_HPP
# define CHUNK_MANAGER_HPP

# include "Noise/Perlin2D.hpp"

# include "Graphics/Shader.hpp"

# include "ValueType/VectorI3.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "Graphics/Texture/Array2D.hpp"

struct Voxel;
struct Chunk;

struct ChunkManager
{
	VoxelGraphics::Shader		Shader;
	Texture::Array2D			Texture;
	Container::Binary<Chunk*>	Chunks;

	~ChunkManager();
	ChunkManager();
	ChunkManager(const ChunkManager & other) = delete;
	ChunkManager & operator=(const ChunkManager & other) = delete;

	const Voxel *	operator[](VectorI3 idx) const;

	unsigned int	FindChunkUndex(Chunk * chunk) const;
	unsigned int	FindChunkUndex(VectorI3 idx) const;
	Chunk *			FindChunkOrNull(VectorI3 idx) const;

	void	Clear();

	void	InsertAround(VectorF3 pos, unsigned int size);
	void	InsertChunk(VectorI3 idx);

	void	RemoveAround(VectorF3 pos, unsigned int size);
	void	RemoveChunk(unsigned int idx);

	bool	ShouldGenerate;
	void	GenerateAround(const Perlin2D & noise, VectorF3 pos, unsigned int size, unsigned int count);

	void	NeighbourInsert(Chunk & chunk);

	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();

	void	Draw();
};

#endif
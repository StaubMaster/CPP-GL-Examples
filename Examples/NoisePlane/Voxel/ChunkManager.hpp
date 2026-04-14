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

	// rename to FindVoxelOrNull ?
			Voxel *	operator[](VectorI3 idx);
	const	Voxel *	operator[](VectorI3 idx) const;

	unsigned int	FindChunkUndex(Chunk * chunk) const;
	unsigned int	FindChunkUndex(VectorI3 idx) const;
	Chunk *			FindChunkOrNull(VectorI3 idx) const;

	void	Clear();
	void	UpdateAround(const Perlin2D & noise, VectorF3 pos);

	bool	ShouldGenerate;
	void	Generate(const Perlin2D & noise, VectorI3 idx);
	void	NeighbourInsert(Chunk & chunk);

	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();

	void	Draw();
};

#endif
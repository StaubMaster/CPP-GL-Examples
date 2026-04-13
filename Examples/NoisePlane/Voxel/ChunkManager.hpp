#ifndef  CHUNK_MANAGER_HPP
# define CHUNK_MANAGER_HPP

# include "Noise/Perlin2D.hpp"

# include "Chunk.hpp"
# include "ChunkGraphics.hpp"
//# include "ChunkNeighbours.hpp"

# include "ValueType/VectorI3.hpp"

# include "Miscellaneous/Container/Binary.hpp"

struct ChunkManager
{
	ChunkGraphics::Shader		Shader;
	Container::Binary<Chunk*>	Chunks;

	~ChunkManager();
	ChunkManager();
	ChunkManager(const ChunkManager & other) = delete;
	ChunkManager & operator=(const ChunkManager & other) = delete;

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
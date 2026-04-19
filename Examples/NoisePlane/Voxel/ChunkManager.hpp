#ifndef  CHUNK_MANAGER_HPP
# define CHUNK_MANAGER_HPP

# include "Noise/Perlin2D.hpp"
# include "Noise/Perlin3D.hpp"

# include "Graphics/Shader.hpp"

# include "ValueType/VectorI3.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "Graphics/Texture/Array2D.hpp"

struct Voxel;
struct Chunk;
enum class Axis : unsigned char;

struct Ray3D;
class PolyHedra;

struct ChunkManager
{
	VoxelGraphics::Shader		Shader;
	Texture::Array2D			Texture;
	Container::Binary<Chunk*>	Chunks;

	~ChunkManager();
	ChunkManager();
	ChunkManager(const ChunkManager & other) = delete;
	ChunkManager & operator=(const ChunkManager & other) = delete;

	PolyHedra *	VoxelBoxPolyHedra;
	PolyHedra *	ChunkBoxPolyHedra;
	PolyHedra *	ViewRayPolyHedra;

	const Voxel *	FindVoxelOrNull(VectorI3 idx) const;
	bool			FindVoxelIndex(Ray3D ray, VectorI3 & idx, Axis & side, Ray3D & hit) const;

	bool	ClearVoxel(VectorI3 idx, Voxel & vox);
	bool	PlaneVoxel(VectorI3 idx, Voxel & vox);

	unsigned int	FindChunkUndex(Chunk * chunk) const;
	unsigned int	FindChunkUndex(VectorI3 idx) const;
	Chunk *			FindChunkOrNull(VectorI3 idx) const;

	void	Clear();

	void	InsertAround(VectorF3 pos, unsigned int size);
	void	InsertChunk(VectorI3 idx);

	void	RemoveAround(VectorF3 pos, unsigned int size);
	void	RemoveChunk(unsigned int idx);

	bool	ShouldGenerate;
	void	GenerateAround(const Perlin2D & noise2, const Perlin3D & noise3, VectorF3 pos, unsigned int size, unsigned int count);

	void	NeighbourInsert(Chunk & chunk);

	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();

	void	Draw();
};

#endif
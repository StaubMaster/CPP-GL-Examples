#ifndef  CHUNK_MANAGER_HPP
# define CHUNK_MANAGER_HPP

# include "ValueGen/Perlin2D.hpp"
# include "ValueGen/Perlin3D.hpp"

# include "Graphics/Shader.hpp"

# include "ValueType/VectorI3.hpp"

# include "Miscellaneous/Container/Binary.hpp"

# include "Graphics/Texture/Array2D.hpp"

//# include "GridCast/GridCast3D.hpp"

struct Voxel;
struct Chunk;
enum class AxisRel : unsigned char;
struct VoxelIndex;

struct Ray3D;
class PolyHedra;

struct VoxelHit
{
	AxisRel		Side;
	VectorI3	Index;
	//VoxelIndex	Index;
	VectorF3	Position;
	VectorF3	Normal;

	bool	Valid() const;
	VoxelHit();
};

struct ChunkManager
{
	VoxelGraphics::Shader		Shader;
	Texture::Array2D			Texture;
	Container::Binary<Chunk*>	Chunks;

	~ChunkManager();
	ChunkManager();
	ChunkManager(const ChunkManager & other) = delete;
	ChunkManager & operator=(const ChunkManager & other) = delete;

	PolyHedra *	VoxelBoxPolyHedra = nullptr;
	PolyHedra *	ChunkBoxPolyHedra = nullptr;
	PolyHedra *	ViewRayPolyHedra = nullptr;

	unsigned int	FindChunkUndex(Chunk * chunk) const;
	unsigned int	FindChunkUndex(VectorI3 idx) const;
	Chunk *			FindChunkOrNull(VectorI3 idx) const;

	VoxelIndex		FindVoxelIndex(VoxelIndex idx) const;
	VoxelIndex		FindVoxelIndex(VectorI3 idx) const;

	const Voxel *	FindVoxelOrNull(VoxelIndex idx) const;
	const Voxel *	FindVoxelOrNull(VectorI3 idx) const;

	VoxelHit		HitVoxel(Ray3D ray) const;



	bool	ClearVoxel(VoxelIndex idx, Voxel & vox);
	bool	ClearVoxel(VectorI3 idx, Voxel & vox);

	bool	PlaceVoxel(VoxelIndex idx, Voxel & vox);
	bool	PlaceVoxel(VectorI3 idx, Voxel & vox);



	bool	DontInsert = false;
	bool	DontRemove = false;
	bool	DontGenerate = false;

	void	Clear();

	void	InsertAround(VectorF3 pos, unsigned int size);
	void	InsertChunk(VectorI3 idx);

	void	RemoveAround(VectorF3 pos, unsigned int size);
	void	RemoveChunk(unsigned int idx);

	void	GenerateAround(const Perlin2D & noise2, const Perlin3D & noise3, VectorF3 pos, unsigned int size, unsigned int count);

	void	NeighbourInsert(Chunk & chunk);

	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();

	void	GraphicsUpdateDataAround(VectorF3 pos, unsigned int count);

	void	Draw();
};

#endif
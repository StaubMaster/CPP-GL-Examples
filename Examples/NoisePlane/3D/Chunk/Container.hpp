#ifndef  CHUNK_CONTAINER_HPP
# define CHUNK_CONTAINER_HPP

# include "ValueType/Vector/I3.hpp"
# include "ValueType/Box/I3.hpp"

struct Chunk;

# include "Generics/Container/Array3D.hpp"

# include "3D/ChunkGuards.hpp"

struct ChunkManager;

# include "Generics/Container/Binary.hpp"

# include "Threading/ObjectLock.hpp"

struct RayF3;

struct VoxelHit;

struct ChunkContainer
{
	public:
	~ChunkContainer();
	ChunkContainer() = delete;
	ChunkContainer(const ChunkContainer & other) = delete;
	ChunkContainer & operator=(const ChunkContainer & other) = delete;
	ChunkContainer(ChunkManager & manager);

	private:
	ChunkManager &	Manager;

	private:
	public:
	Array3D<Chunk*>		Chunks;
	ObjectLock			ChunksLock;

	private: public:
	unsigned int	KnowSize;
	unsigned int	CareSize;

	private:
	VectorI3	Center;
	BoxI3		KnowBox;
	BoxI3		CareBox;

	public:
	bool	AbsoluteCheckCareBox(const VectorI3 & idx) const;
	bool	AbsoluteCheckKnowBox(const VectorI3 & idx) const;

	private:
	VectorI3	RelativeToAbsolute(VectorU3 u) const;
	VectorU3	AbsoluteToRelative(VectorI3 i) const;
	public:
	VectorI3	CenteredToAbsolute(VectorI3 i) const;
	VectorI3	AbsoluteToCentered(VectorI3 i) const;

	public:
	Chunk *		FindAbsolutePointer(VectorI3 idx);
	Chunk *		FindCenteredPointer(VectorI3 idx);

	public:
	AccessLockedChunk	FindAbsoluteAccess(VectorI3 idx);

	public:
	void	Clear();
	void	ChangeSize(unsigned int know_size, unsigned int care_size);
	void	ChangeCenter(VectorI3 center);

	private:
	public:
	Container::Binary<Chunk*>	ChunksToInsert; // do this in Chunks
	Container::Binary<Chunk*>	ChunksToRemove; // ChunkDisposal
	ObjectLock					ChunksToInsertLock;
	ObjectLock					ChunksToRemoveLock;

	private:
	void	ChunkNeighboutsFind(Chunk & chunk);

	private:
	void	PutChunks(Container::Binary<VectorI3> & chunks);

	private:
	Container::Binary<VectorI3>		MissingCareChunks();

	private:
	void	PutMissingCareChunks();

	public:
	void	UpdateChunksContainer();

	public:
	VoxelHit	HitVoxel(RayF3 ray);
};

#endif
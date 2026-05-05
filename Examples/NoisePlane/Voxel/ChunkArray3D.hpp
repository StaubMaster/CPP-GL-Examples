#ifndef  CHUNK_ARRAY_3D_HPP
# define CHUNK_ARRAY_3D_HPP

# include "Chunk.hpp"
# include "ValueType/VectorU3.hpp"
# include "ValueType/VectorI3.hpp"

struct ChunkArray3D
{
	Chunk * *	Data;
	VectorU3	Size;
//	VectorU3	Half;

	VectorI3	Center;
	VectorI3	Corner;

	unsigned int	Count() const;

	Chunk * &	operator[](unsigned int idx);
	Chunk * &	operator[](VectorU3 idx);

	Chunk *		FindLockOrNull(VectorI3 idx);
	Chunk *		FindTryLockOrNull(VectorI3 idx);

	VectorI3	absolute(VectorU3 u) const;
	VectorU3	relative(VectorI3 i) const;

	~ChunkArray3D();
	ChunkArray3D();
	ChunkArray3D(const ChunkArray3D & other) = delete;
	ChunkArray3D & operator=(const ChunkArray3D & other) = delete;
};

#endif
#ifndef  CHUNK_VALUE_HPP
# define CHUNK_VALUE_HPP

# include "Voxel.hpp"

# include "ValueType/ColorF4.hpp"
# include "ValueType/VectorU3.hpp"

struct ChunkValue
{
	bool		Known;
	Voxel		Value; // Pointer ?

	~ChunkValue();
	ChunkValue();
	ChunkValue(const ChunkValue & other);
	ChunkValue & operator=(const ChunkValue & other);

	bool	IsSolid() const;
	void	Change(Voxel val);
};

#endif
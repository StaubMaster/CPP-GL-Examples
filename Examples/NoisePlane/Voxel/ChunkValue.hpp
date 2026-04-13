#ifndef  CHUNK_VALUE_HPP
# define CHUNK_VALUE_HPP

# include "ValueType/ColorF4.hpp"
# include "ValueType/VectorU3.hpp"

struct ChunkValue
{
	bool		Known;
	float		Value;

	~ChunkValue();
	ChunkValue();
	ChunkValue(const ChunkValue & other);
	ChunkValue & operator=(const ChunkValue & other);

	bool	Check(float val) const;
	void	Change(float val);
};

#endif
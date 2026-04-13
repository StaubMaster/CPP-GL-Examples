#ifndef  CHUNK_VALUE_HPP
# define CHUNK_VALUE_HPP

# include "ValueType/ColorF4.hpp"
# include "ValueType/VectorU3.hpp"

struct ChunkValue
{
	bool		Known;
	VectorU3	Undex;
	float		Value;

	~ChunkValue();
	ChunkValue();
	ChunkValue(const ChunkValue & other);
	ChunkValue & operator=(const ChunkValue & other);

	void		Change(VectorU3 udx, float val);
	ColorF4		ToColor() const;
};

#endif
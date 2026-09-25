#ifndef  POLYHEDRA_DATA_HPP
# define POLYHEDRA_DATA_HPP

# include "PolyHedra.hpp"

# include "ValueType/Vector/F3.hpp"

struct PolyHedra::Corner
{
	VectorF3	Position;

	~Corner() = default;
	Corner() = default;
	Corner(const Corner & other) = default;
	Corner & operator=(const Corner & other) = default;

	Corner(VectorF3 pos);
	Corner(float x, float y, float z);
};
struct PolyHedra::Face
{
	unsigned int	idx[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
	unsigned int	NormalGroup = 0xFFFFFFFF;
	VectorF3		Normal; // Calculate when Buffer is made ?

	bool	Check(unsigned int count) const;

	~Face() = default;
	Face() = default;
	Face(const Face & other) = default;
	Face & operator=(const Face & other) = default;

	Face(unsigned int idx0, unsigned int idx1, unsigned int idx2);
	Face(unsigned int idx0, unsigned int idx1, unsigned int idx2, unsigned int normal_group);
};
struct PolyHedra::Edge
{
	unsigned int	idx[2] = { 0xFFFFFFFF, 0xFFFFFFFF };

	bool	Check(unsigned int count) const;

	~Edge() = default;
	Edge() = default;
	Edge(const Edge & other) = default;
	Edge & operator=(const Edge & other) = default;

	Edge(unsigned int idx0, unsigned int idx1);
};

#endif
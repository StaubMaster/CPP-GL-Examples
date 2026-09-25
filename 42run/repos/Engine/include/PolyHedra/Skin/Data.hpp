#ifndef  SKIN_DATA_HPP
# define SKIN_DATA_HPP

# include "Skin.hpp"

# include "ValueType/Vector/F2.hpp"
# include "ValueType/Color/F4.hpp"

struct Skin::Corner
{
	VectorF2		Coord;
	unsigned int	Index = 0xFFFFFFFF;
	ColorF4			Color;

	~Corner() = default;
	Corner() = default;
	Corner(const Corner & other) = default;
	Corner & operator=(const Corner & other) = default;

	Corner(VectorF2 coord, unsigned int index);
	Corner(float coord_x, float coord_y, unsigned int index);
	Corner(ColorF4 color);
};
struct Skin::Face
{
	unsigned int	idx[3] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
	// Texture Index here ?

	~Face() = default;
	Face() = default;
	Face(const Face & other) = default;
	Face & operator=(const Face & other) = default;

	Face(unsigned int idx0, unsigned int idx1, unsigned int idx2);
};

#endif

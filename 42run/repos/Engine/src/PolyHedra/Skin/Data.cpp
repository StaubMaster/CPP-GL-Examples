#include "PolyHedra/Skin/Data.hpp"



Skin::Corner::Corner(VectorF2 coord, unsigned int index)
	: Coord(coord)
	, Index(index)
{ }
Skin::Corner::Corner(float coord_x, float coord_y, unsigned int index)
	: Coord(coord_x, coord_y)
	, Index(index)
{ }
Skin::Corner::Corner(ColorF4 color)
	: Color(color)
{ }



Skin::Face::Face(unsigned int idx0, unsigned int idx1, unsigned int idx2)
	: idx{ idx0, idx1, idx2 }
{ }

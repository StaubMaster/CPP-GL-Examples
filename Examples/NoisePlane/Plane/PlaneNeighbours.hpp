#ifndef  PLANE_NEIGHBOURS_HPP
# define PLANE_NEIGHBOURS_HPP

# include "PlaneValue.hpp"

struct Plane;

struct PlaneNeighbours
{
	// should each chunk store its neightours ?
//	Plane *		Planes[9];
	Plane *		Planes[4];

	~PlaneNeighbours();
	PlaneNeighbours();
	PlaneNeighbours(const PlaneNeighbours & other);
	PlaneNeighbours & operator=(const PlaneNeighbours & other);

	PlaneValue	Value(unsigned int plane_idx, unsigned int tile_idx) const;
};

#endif
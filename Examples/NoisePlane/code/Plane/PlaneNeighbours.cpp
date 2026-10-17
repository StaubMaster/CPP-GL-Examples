#include "PlaneNeighbours.hpp"
#include "Plane.hpp"



PlaneNeighbours::~PlaneNeighbours() { }
PlaneNeighbours::PlaneNeighbours()
	/*: Planes{
		nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr
	}*/
	: Planes{
		nullptr, nullptr,
		nullptr, nullptr,
	}
{ }
PlaneNeighbours::PlaneNeighbours(const PlaneNeighbours & other)
	/*: Planes{
		other.Planes[0], other.Planes[1], other.Planes[2],
		other.Planes[3], other.Planes[4], other.Planes[5],
		other.Planes[6], other.Planes[7], other.Planes[8]
	}*/
	: Planes{
		other.Planes[0b00], other.Planes[0b01],
		other.Planes[0b10], other.Planes[0b11],
	}
{ }
PlaneNeighbours & PlaneNeighbours::operator=(const PlaneNeighbours & other)
{
	//Planes[0] = other.Planes[0];
	//Planes[1] = other.Planes[1];
	//Planes[2] = other.Planes[2];
	//Planes[3] = other.Planes[3];
	//Planes[4] = other.Planes[4];
	//Planes[5] = other.Planes[5];
	//Planes[6] = other.Planes[6];
	//Planes[7] = other.Planes[7];
	//Planes[8] = other.Planes[8];
	Planes[0b00] = other.Planes[0b00];
	Planes[0b01] = other.Planes[0b01];
	Planes[0b10] = other.Planes[0b10];
	Planes[0b11] = other.Planes[0b11];
	return *this;
}

PlaneValue PlaneNeighbours::Value(unsigned int plane_idx, unsigned int tile_idx) const
{
	PlaneValue val;
	if (Planes[plane_idx] != nullptr)
	{
		val.Value = (*Planes[plane_idx]).Values[tile_idx];
		val.Known = true;
	}
	return val;
}

#ifndef  PLANE_MANAGER_HPP
# define PLANE_MANAGER_HPP

# include "Perlin2D.hpp"
# include "Plane.hpp"
# include "PlaneGraphics.hpp"

# include "ValueType/ColorF4.hpp"

struct PlaneValue
{
	bool	Known;
	float	Value;
	// Position ?

	~PlaneValue();
	PlaneValue();
	PlaneValue(const PlaneValue & other);
	PlaneValue & operator=(const PlaneValue & other);

	ColorF4		ToColor() const;
};

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

# define PLANES_PER_SIDE 32
# define PLANES_PER_AREA PLANES_PER_SIDE * PLANES_PER_SIDE

struct PlaneManager
{
	PlaneGraphics::Shader	Shader;
	PlaneGraphics::Buffer	Buffers[PLANES_PER_AREA];

	Plane		Planes[PLANES_PER_AREA];

	~PlaneManager();
	PlaneManager();
	PlaneManager(const PlaneManager & other) = delete;
	PlaneManager & operator=(const PlaneManager & other) = delete;

	void	PlanesGenerate(const Perlin2D & noise);
	void	PlanesToBuffers();

	PlaneNeighbours		NeighboursAround(Undex2D udx);
	static void			PlaneToMainBuffer(const PlaneNeighbours & neighbours, PlaneGraphics::MainBuffer & buffer);

	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();
	void	Draw();
};

#endif
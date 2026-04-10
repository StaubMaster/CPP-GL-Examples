#ifndef  PLANE_HPP
# define PLANE_HPP

# define PLANE_SCALE 0.0625
# define PLANE_VALUES_PER_SIDE 16
# define PLANE_VALUES_PER_AREA PLANE_VALUES_PER_SIDE * PLANE_VALUES_PER_SIDE

# include "ValueType/Undex2D.hpp"
# include "PlaneGraphics.hpp"
# include "PlaneNeighbours.hpp"

struct Perlin2D;

struct Plane
{
	float				Values[PLANE_VALUES_PER_AREA];
	Undex2D				Undex;
	PlaneNeighbours		Neighbours;

	float &			operator[](Undex2D udx);
	const float &	operator[](Undex2D udx) const;

	~Plane();
	Plane();
	Plane(const Plane & other) = delete;
	Plane & operator=(const Plane & other) = delete;

	bool	IsGenerated;
	void	Generate(const Perlin2D & noise);



	PlaneGraphics::Buffer	Buffer;

	bool	GraphicsExist;
	void	GraphicsCreate();
	void	GraphicsDelete();

	bool	BufferNeedsInit;

	bool	MainBufferNeedsData;
	void	UpdateMainBuffer();

	bool	InstBufferNeedsData;
	void	UpdateInstBuffer();

	void	Draw();
};

#endif

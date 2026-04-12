#ifndef  PLANE_HPP
# define PLANE_HPP

# define PLANE_SCALE 0.0625
# define PLANE_VALUES_PER_SIDE 16
# define PLANE_VALUES_PER_AREA PLANE_VALUES_PER_SIDE * PLANE_VALUES_PER_SIDE

# include "ValueType/VectorI2.hpp"
# include "ValueType/VectorU2.hpp"

# include "PlaneGraphics.hpp"
# include "PlaneNeighbours.hpp"

struct Perlin2D;

struct Plane
{
	float				Values[PLANE_VALUES_PER_AREA];
	VectorI2			Index;
	PlaneNeighbours		Neighbours;

	float &			operator[](VectorU2 udx);
	const float &	operator[](VectorU2 udx) const;

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

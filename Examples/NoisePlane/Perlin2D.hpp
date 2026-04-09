#ifndef  PERLIN_2D_HPP
# define PERLIN_2D_HPP

# include "ValueType/Undex2D.hpp"
# include "ValueType/Point2D.hpp"

struct Perlin2D
{
	Undex2D		Count;
	Point2D *	Data;

	~Perlin2D();
	Perlin2D();
	Perlin2D(const Perlin2D & other);
	Perlin2D & operator=(const Perlin2D & other);
	
	Perlin2D(Undex2D count);

	static Perlin2D		Random(Undex2D count);

	Undex2D		Normalize(Point2D node) const;

	float	Calculate(Point2D pos) const;

	static void		DebugClear();
	static void		DebugShow();
};

#endif
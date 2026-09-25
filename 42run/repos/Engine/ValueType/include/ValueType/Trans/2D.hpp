#ifndef  TRANS_2D_HPP
# define TRANS_2D_HPP

# include "ValueType/Vector/F2.hpp"
# include "ValueType/Angle.hpp"

struct RayF2;
struct LineF2;

struct Trans2D
{
	VectorF2		Pos; // Position
	Angle		Rot; // Rotation



	~Trans2D();

	Trans2D();
	Trans2D(VectorF2 pos);
	Trans2D(VectorF2 pos, Angle rot);

	Trans2D(const Trans2D & other);
	Trans2D & operator=(const Trans2D & other);



	VectorF2		forward(VectorF2 p) const;
	VectorF2		reverse(VectorF2 p) const;

	RayF2		forward(RayF2 ray) const;
	RayF2		reverse(RayF2 ray) const;
};

#endif

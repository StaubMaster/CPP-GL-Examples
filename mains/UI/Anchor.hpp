#ifndef  ANCHOR_HPP
# define ANCHOR_HPP



#define ANCHOR_NONE 0b00
#define ANCHOR_MIN  0b01
#define ANCHOR_MAX  0b10
#define ANCHOR_BOTH 0b11



struct Point2D;
struct AxisBox1D;
struct AxisBox2D;



struct Anchor1D
{
	unsigned char Anchor;

	AxisBox1D Calculate(AxisBox1D Dist, float Size, float NormalCenter, AxisBox1D Parent);
};

struct Anchor2D
{
	Anchor1D	X;
	Anchor1D	Y;

	AxisBox2D Calculate(AxisBox2D Dist, Point2D Size, Point2D NormalCenter, AxisBox2D Parent);
};

#endif
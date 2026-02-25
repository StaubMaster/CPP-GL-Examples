#ifndef  WIREFRAME_2D_HPP
# define WIREFRAME_2D_HPP

# include "Miscellaneous/Container/Binary.hpp"
# include "ValueType/Point2D.hpp"
# include "ValueType/ColorF4.hpp"

struct AxisBox2D;

class WireFrame2D
{
	public:
	struct Corner
	{
		Point2D	Pos;
		ColorF4	Col;
		Corner();
		Corner(Point2D pos);
		Corner(Point2D pos, ColorF4 col);
	};
	struct Side
	{
		unsigned int udx[2];
		Side();
		Side(unsigned int udx0, unsigned int udx1);
	};

	public:
	Container::Binary<Corner>	Corners;
	Container::Binary<Side>		Sides;

	public:
	~WireFrame2D();
	WireFrame2D();

	WireFrame2D(const WireFrame2D & other) = delete;
	WireFrame2D & operator=(const WireFrame2D & other) = delete;

	public:
	void Clear();

	public:
	void Insert_Corner(Point2D pos);
	void Insert_Corner(Point2D pos, ColorF4 col);
	void Insert_Side(unsigned int udx0, unsigned int udx1);

	void Insert_Box(AxisBox2D box, ColorF4 col);
};

#endif
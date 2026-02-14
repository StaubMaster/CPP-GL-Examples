#ifndef  POLYGON_DATA_HPP
# define POLYGON_DATA_HPP

# include "PolyGon.hpp"

# include "ValueType/Point2D.hpp"
# include "ValueType/ColorF4.hpp"

struct PolyGon::Corner
{
	Point2D	Pos;
	ColorF4	Col;
	Corner();
	Corner(Point2D pos);
	Corner(Point2D pos, ColorF4 col);
};
struct PolyGon::SideCorner
{
	unsigned int Udx;
	SideCorner();
	SideCorner(unsigned int udx);
};
struct PolyGon::Side
{
	SideCorner	Corner0;
	SideCorner	Corner1;
	SideCorner	Corner2;
	Side();
	Side(SideCorner c0, SideCorner c1, SideCorner c2);
};

#endif
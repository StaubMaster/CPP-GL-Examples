#ifndef  POLYGON_HPP
# define POLYGON_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/ColorF4.hpp"

# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Container/Pointer.hpp"
# include "Physics2D/Main/Data.hpp"

class PolyGon
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
	struct SideCorner
	{
		unsigned int Udx;
		SideCorner();
		SideCorner(unsigned int udx);
	};
	struct Side
	{
		SideCorner	Corner0;
		SideCorner	Corner1;
		SideCorner	Corner2;
		Side();
		Side(SideCorner c0, SideCorner c1, SideCorner c2);
	};

	public:
	Container::Binary<Corner>	Corners;
	Container::Binary<Side>		Sides;

	public:
	PolyGon();
	~PolyGon();

	PolyGon(const PolyGon & other) = delete;
	PolyGon & operator=(const PolyGon & other) = delete;

	public:
	void Clear();

	Container::Pointer<Physics2D::Main::Data>	ToPhysics2D() const;
};

#endif
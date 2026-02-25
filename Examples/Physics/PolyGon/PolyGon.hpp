#ifndef  POLYGON_HPP
# define POLYGON_HPP

# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Container/Pointer.hpp"
# include "PolyGon/Graphics/Data.hpp"

struct Ray2D;
struct AxisBox2D;

class PolyGon
{
	public:
	struct Corner;
	struct SideCorner;
	struct Side;

	public:
	Container::Binary<Corner>	Corners;
	Container::Binary<Side>		Sides;

	public:
	~PolyGon();
	PolyGon();

	PolyGon(const PolyGon & other) = delete;
	PolyGon & operator=(const PolyGon & other) = delete;

	public:
	void Clear();

	AxisBox2D ToAxisBox() const;
	Container::Pointer<PolyGonGraphics::Data>	ToMainData() const;

	public:
	bool IsIntersecting(Ray2D ray) const;
	bool IsContaining(Point2D p) const;
};

#endif
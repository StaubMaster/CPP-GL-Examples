#ifndef  POLYGON_HPP
# define POLYGON_HPP

# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Container/Pointer.hpp"
# include "Main/Data.hpp"

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
	PolyGon();
	~PolyGon();

	PolyGon(const PolyGon & other) = delete;
	PolyGon & operator=(const PolyGon & other) = delete;

	public:
	void Clear();

	Container::Pointer<Physics2D::Main::Data>	ToPhysics2D() const;
};

#endif
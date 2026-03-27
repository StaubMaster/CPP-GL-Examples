#ifndef  POLYGON_HPP
# define POLYGON_HPP

# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Container/Pointer.hpp"
# include "PolyGon/Graphics/Full/Main/Data.hpp"

struct Ray2D;
struct AxisBox2D;

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
	struct Face
	{
		unsigned int udx[3];
		bool Check(unsigned int count) const;
		Face();
		Face(unsigned int u0, unsigned int u1, unsigned int u2);
	};
	struct Edge
	{
		unsigned int udx[2];
		bool Check(unsigned int count) const;
		Edge();
		Edge(unsigned int u0, unsigned int u1);
	};

	public:
	Container::Binary<Corner>		Corners;
	Container::Binary<Face>			Faces;
	Container::Binary<Edge>			Edges;

	public:
	~PolyGon();
	PolyGon();

	PolyGon(const PolyGon & other) = delete;
	PolyGon & operator=(const PolyGon & other) = delete;

	public:
	void Clear();
	void NewCorner(Point2D pos, ColorF4 col);
	void NewFace(unsigned int c0, unsigned int c1, unsigned int c2);

	AxisBox2D ToAxisBox() const;
	Container::Pointer<PolyGonFull::Main::Data>	ToFullData() const;

	public:
	unsigned int SumIntersections(Ray2D ray) const;
	bool IsContaining(Point2D p) const;
};

#endif
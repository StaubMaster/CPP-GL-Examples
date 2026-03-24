#ifndef  POLYGON_OBJECT_HPP
# define POLYGON_OBJECT_HPP

# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Container/Pointer.hpp"
# include "PolyGon/Graphics/Full/Data.hpp"

struct Ray2D;
struct AxisBox2D;

namespace PolyGon
{
class Object
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
	~Object();
	Object();

	Object(const Object & other) = delete;
	Object & operator=(const Object & other) = delete;

	public:
	void Clear();
	void NewCorner(Point2D pos, ColorF4 col);
	void NewFace(unsigned int c0, unsigned int c1, unsigned int c2);

	AxisBox2D ToAxisBox() const;
	Container::Pointer<PolyGon::Full::Data>	ToFullData() const;

	public:
	unsigned int SumIntersections(Ray2D ray) const;
	bool IsContaining(Point2D p) const;
};
};

#endif
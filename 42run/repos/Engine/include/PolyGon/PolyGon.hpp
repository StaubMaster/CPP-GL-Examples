#ifndef  POLYGON_HPP
# define POLYGON_HPP

# include "Generics/Container/Binary.hpp"
# include "Generics/Container/Array.hpp"
# include "PolyGon/Graphics/Full/Main/Data.hpp"

struct RayF2;
//struct BoxF2;
struct BoxF2;
typedef BoxF2 BoxF2;

class PolyGon
{
	public:
	struct Corner
	{
		VectorF2	Pos;
		ColorF4	Col;
		Corner();
		Corner(VectorF2 pos);
		Corner(VectorF2 pos, ColorF4 col);
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
	void NewCorner(VectorF2 pos, ColorF4 col);
	void NewFace(unsigned int c0, unsigned int c1, unsigned int c2);

	BoxF2 ToAxisBox() const;
	Container::Array<PolyGonFull::Main::Data>	ToFullData() const;

	public:
	unsigned int SumIntersections(RayF2 ray) const;
	bool IsContaining(VectorF2 p) const;
};

#endif
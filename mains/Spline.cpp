
#include "DataInclude.hpp"
#include "DataShow.hpp"

struct SplineNode3D
{
	Point3D	Pos;
	Point3D	Dir;
};

struct SplineSegment3D
{
	SplineNode3D	Node0;
	SplineNode3D	Node1;

/*	PlaceHolder
		I remember there being 3 Valus that can be used to modify the Spline
*/
	float	A;
	float	B;
	float	C;

	SplineNode3D	Calculate(float t) const
	{
		/*	PlaceHolder
				I cant remember how this works
				Linear Interpolation for now
		*/

		LInter linter;
		linter.SetT0(t);

		SplineNode3D node;

		node.Pos.X = linter.Calc(Node0.Pos.X, Node1.Pos.X);
		node.Pos.Y = linter.Calc(Node0.Pos.Y, Node1.Pos.Y);
		node.Pos.Z = linter.Calc(Node0.Pos.Z, Node1.Pos.Z);

		node.Dir.X = linter.Calc(Node0.Dir.X, Node1.Dir.X);
		node.Dir.Y = linter.Calc(Node0.Dir.Y, Node1.Dir.Y);
		node.Dir.Z = linter.Calc(Node0.Dir.Z, Node1.Dir.Z);

		return node;
	}
};

struct SplineCurve3D
{
	SplineSegment3D	* Segments;
	unsigned int SegmentCount;

	SplineCurve3D(SplineNode3D * nodes, unsigned int count, bool closed)
	{
		count--;
		SegmentCount = count;
		if (closed) { SegmentCount++; }
		Segments = new SplineSegment3D[SegmentCount];

		for (unsigned int i = 0; i < count; i++)
		{
			Segments[i].Node0 = nodes[i + 0];
			Segments[i].Node1 = nodes[i + 1];
		}
		if (closed)
		{
			Segments[count].Node0 = nodes[count];
			Segments[count].Node1 = nodes[0];
		}
	}
	~SplineCurve3D()
	{
		delete [] Segments;
	}

	SplineNode3D	Calculate(float t) const
	{
		//	Modulate t into range [ 0 ; SegmentCount - 1]
		{
			while (t < 0) { t += SegmentCount; }
			while (t > SegmentCount - 1) { t -= SegmentCount; }
		}

		unsigned int idx = t;	//	floors ?
		return Segments[idx].Calculate(t - idx);
	}
};

struct SplineObject
{
	unsigned int	Index;
	float			SplineValue;
};

SplineCurve3D * Spline;



//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Drehgestell_Achse.polyhedra.ymt"));
//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Drehgestell_Halter.polyhedra.ymt"));	//	Faces wrong way
//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Drehgestell_Rahmen.polyhedra.ymt"));	//	Faces Wrong way
//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Gleis_Seg.polyhedra.ymt"));				//	Faces Wrong way
//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Schienen_Seg.polyhedra.ymt"));			//	Faces Wrong way
//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Wagen_Flach.polyhedra.ymt"));			//	Faces Wrong way, some Geometry Wrong
//YMT::PolyHedra::Load(FileContext("../media/YMT/Spline/Wagen_Tief.polyhedra.ymt"));			//	Faces Wrong way, some Geometry Wrong



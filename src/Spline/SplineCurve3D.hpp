#ifndef  SPLINE_CURVE_3D_HPP
# define SPLINE_CURVE_3D_HPP

# include "SplineSegment3D.hpp"
# include "SplineNode3D.hpp"

struct SplineCurve3D
{
	SplineSegment3D	* Segments;
	unsigned int SegmentCount;

	SplineCurve3D(SplineNode3D * nodes, unsigned int count, bool closed, float t, float c, float b)
	{
		count--;
		SegmentCount = count;
		if (closed) { SegmentCount++; }
		Segments = new SplineSegment3D[SegmentCount];

		unsigned int min = 0;
		unsigned int max = SegmentCount - 1;

		for (unsigned int i = min; i < max; i++)
		{
			Segments[i] = SplineSegment3D(nodes[i + 0], nodes[i + 1], t, c, b);
		}
		if (closed)
		{
			Segments[count] = SplineSegment3D(nodes[max], nodes[min], t, c, b);
		}

		for (unsigned int i = 0; i < SegmentCount; i++)
		{
			if (i == min)
			{ Segments[i].Prev = &Segments[max]; }
			else
			{ Segments[i].Prev = &Segments[i - 1]; }

			if (i == max)
			{ Segments[i].Next = &Segments[min]; }
			else
			{ Segments[i].Next = &Segments[i + 1]; }
		}
	}
	~SplineCurve3D()
	{
		delete [] Segments;
	}

	SplineNode3D	CalculateLerp(float t) const
	{
		//	Modulate t into range [ 0 ; SegmentCount - 1]
		{
			while (t < 0) { t += SegmentCount; }
			while (t > SegmentCount) { t -= SegmentCount; }
		}

		unsigned int idx = t;	//	floors ?
		return Segments[idx].CalculateLerp(t - idx);
	}
	SplineNode3D	Calculate(float t) const
	{
		//	Modulate t into range [ 0 ; SegmentCount - 1]
		{
			while (t < 0) { t += SegmentCount; }
			while (t > SegmentCount) { t -= SegmentCount; }
		}

		unsigned int idx = t;	//	floors ?
		return Segments[idx].Calculate(t - idx);
	}
};

#endif
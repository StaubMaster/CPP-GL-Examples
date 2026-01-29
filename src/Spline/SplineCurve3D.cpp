#include "SplineCurve3D.hpp"
#include <math.h>



void SplineCurve3D::SetT(float val)
{
	T = val;
	for (unsigned int i = 0; i < SegmentCount; i++)
	{
		Segments[i].T = val;
	}
}
void SplineCurve3D::SetB(float val)
{
	B = val;
	for (unsigned int i = 0; i < SegmentCount; i++)
	{
		Segments[i].B = val;
	}
}
void SplineCurve3D::SetC(float val)
{
	C = val;
	for (unsigned int i = 0; i < SegmentCount; i++)
	{
		Segments[i].C = val;
	}
}

void SplineCurve3D::CalcTBCFromSegments()
{
	if (SegmentCount == 0)
	{
		T = NAN;
		B = NAN;
		C = NAN;
	}
	else
	{
		T = Segments[0].T;
		B = Segments[0].B;
		C = Segments[0].C;
		for (unsigned int i = 1; i < SegmentCount; i++)
		{
			if (Segments[i - 1].T != Segments[i - 0].T) { T = NAN; }
			if (Segments[i - 1].B != Segments[i - 0].B) { B = NAN; }
			if (Segments[i - 1].C != Segments[i - 0].C) { C = NAN; }
		}
	}
}

SplineCurve3D::SplineCurve3D(SplineNode3D * nodes, unsigned int count, bool closed, float t, float b, float c)
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
SplineCurve3D::~SplineCurve3D()
{
	delete [] Segments;
}

SplineNode3D	SplineCurve3D::CalculateLerp(float t) const
{
	//	Modulate t into range [ 0 ; SegmentCount - 1]
	{
		while (t < 0) { t += SegmentCount; }
		while (t > SegmentCount) { t -= SegmentCount; }
	}

	unsigned int idx = t;	//	floors ?
	return Segments[idx].CalculateLerp(t - idx);
}
SplineNode3D	SplineCurve3D::Calculate(float t) const
{
	//	Modulate t into range [ 0 ; SegmentCount - 1]
	{
		while (t < 0) { t += SegmentCount; }
		while (t > SegmentCount) { t -= SegmentCount; }
	}

	unsigned int idx = t;	//	floors ?
	return Segments[idx].Calculate(t - idx);
}

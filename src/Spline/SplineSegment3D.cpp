#include "SplineSegment3D.hpp"
#include "Factors.hpp"
#include "ValueType/LInter.hpp"



Factors<float> Factors_TBC(float T, float B, float C)
{
	float Tm = 1 - T;
	float Bm = 1 - B;
	float Bp = 1 + B;
	float Cm = 1 - C;
	float Cp = 1 + C;
	Factors<float> factors(4);
	factors[0] = (Tm * Bp * Cm) / 2;
	factors[1] = (Tm * Bm * Cp) / 2;
	factors[2] = (Tm * Bp * Cp) / 2;
	factors[3] = (Tm * Bm * Cm) / 2;
	return factors;
}
/*
	these are used for Trangent calculation so I assume they are Defivatives ?
h[00] = -(3t^3) + 3 * (2t^2) - 3;
h[01] = +(3t^3) - 2 * (2t^2) + 1;
h[10] = -(3t^3) + 1 * (2t^2);
h[11] = +(3t^3);

the originals are
h[00] = +2(t^3) - 3(t^2) + 1
h[01] = +1(t^3) - 2(t^2) + t
h[10] = -2(t^3) - 3(t^2)
h[11] = +1(t^3) - 1(t^2)

Derivatives would have all t^3 converted to 3t^2
so there whould be no t^3 left
there are also no t^1
wtf are these ?
where did I get them ?

hold up the real factors are
h[00] = -(3t^2) + 3(2t^1) - 3;
h[01] = +(3t^2) - 2(2t^1) + 1;
h[10] = -(3t^2) + 1(2t^1);
h[11] = +(3t^2);

all the 3t^2 and 2t^1 are the result of deriving
so they look right ?
deriving the originals would give

h[00] = +2(3t^2) - 3(2t^1)
h[01] = +1(3t^2) - 2(2t^1) + 1
h[10] = -2(3t^2) - 3(2t^1)
h[11] = +1(3t^2) - 1(2t^1)

try using these ?

it worked ??
but where did I get those first factors ?

*/
Factors<float> Factors_T_Something(float t)
{
	float factorDir3 = t * t * 3;
	float factorDir2 = t * 2;
	Factors<float> factors(4);
	factors[0] = -factorDir3 + 3 * factorDir2 - 3;
	factors[1] = +factorDir3 - 2 * factorDir2 + 1;
	factors[2] = -factorDir3 + 1 * factorDir2;
	factors[3] = +factorDir3;
	return factors;
}



SplineSegment3D::SplineSegment3D()
{ }
SplineSegment3D::SplineSegment3D(SplineNode3D node0, SplineNode3D node1, float t, float b, float c)
{
	Node0 = node0;
	Node1 = node1;
	Prev = 0;
	Next = 0;

	T = t;
	B = b;
	C = c;
}





SplineNode3D SplineSegment3D::InterpolateLinear(float t) const
{
	LInter linter;
	linter.SetT1(t);

	SplineNode3D node;

	node.Pos.X = linter.Calc(Node0.Pos.X, Node1.Pos.X);
	node.Pos.Y = linter.Calc(Node0.Pos.Y, Node1.Pos.Y);
	node.Pos.Z = linter.Calc(Node0.Pos.Z, Node1.Pos.Z);

	node.Dir.X = linter.Calc(Node0.Dir.X, Node1.Dir.X);
	node.Dir.Y = linter.Calc(Node0.Dir.Y, Node1.Dir.Y);
	node.Dir.Z = linter.Calc(Node0.Dir.Z, Node1.Dir.Z);

	return node;
}



/*	Problem:
this spline used 3 Control Points
one being in the middle
but the way I do splines is that I need a Segment
in which to interpolate

         |
A-----B-----C-----D
#-----#-----#		Spline1
      #-----#-----#	Spline2
if I have 4 Control Points
it forms 3 of these Splines
should a point between B and C
be calculated with Spline1 or Spline2 ?

what if they have different TCB parameters ?

just choose interpolate based on the closest ControlPoint
of if its between 0.5 and 1.5, choose Spline1
from 1.5 to 2.5, choose Spline2

make an Interpolator base class ?
so that Linear and that stuff are all seperate ?
first make this Spline, then do that



hold on
the Bernstein stuff shows the Spline going between 2 ControlPoints ???

calculating a Tangent can be done using 3 ControlPoints
mk = ((p[k] - p[k-1]) + (p[k+1] - p[k])) / 2
basically just the average of differances

Catmull-Rom-Spline:
{
mk = ((p[k] - p[k-1]) + (p[k+1] - p[k])) / 2
can be simplified to
m = (p[k-1] + p[k+1]) / 2
which can be multiplied with a factor
to get the Catmull-Rom-Spline
mk = ((p[k-1] + p[k+1]) / 2) * Tk
}

should I store the Nodes seperatly ?
right now each Segment has its own Node0 and Node1
which can cause segments to be disconnected ?
however, disconnection should exist at the start and end of the Curve, not in the middle ?

Cardinal Spline
{
mk = (1-ck)/2  * (p[k+1] - p[k-1])
with ck [-1:+1]
ck is a Tension ???
}

Kochanek-Bartels-Spline	(TCB-Spline)
{
different Tangent at ControlPoint
...
}

all these calculate the Tangent ?
so all this can be done manually by just specifying a Tangent ?



to Calculate the Tangent, you need 3 ControlPoints
to Interpolate, you only need 2 ControlPoints (?)



the factors are needed
how to I sum/factor with my Nodes to get a Point and Tangent ?

expanded
h[00]	+2t^3 - 3t^2 + 1
h[01]	  t^3 - 2t^2 + t
h[10]	-2t^3 - 3t^2
h[11]	  t^3 -  t^2

factorized
h[00]	(1 + 2t)(1 - t)^2
h[01]	t(1 - t)^2
h[10]	t^2(3 - 2t)
h[11]	t^2(t - 1)

the Point on the Spline is the sum of
	h[00] * p[0]
	h[01] * m[0]
	h[10] * p[1]
	h[11] * m[1]
how do I get a Tangent ?
something about derivatives ?

*/
SplineNode3D SplineSegment3D::InterpolateCubicHermite(float t) const
{
	Factors<float> factorsPos(4);
	{
		float t0 = 1;
		float t1 = t0 * t;
		float t2 = t1 * t;
		float t3 = t2 * t;
		factorsPos[0] = (2 * t3) - (3 * t2) + (1 * t0);
		factorsPos[1] = t3 - (2 * t2) + t1;
		factorsPos[2] = -(2 * t3) + (3 * t2);
		factorsPos[3] = t3 - t2;
	}

	Factors<float> factorsDir(4);
	{
		float t0 = 0;
		float t1 = 1;
		float t2 = 2 * t;
		float t3 = 3 * t * t;
		factorsDir[0] = (2 * t3) - (3 * t2) + (1 * t0);
		factorsDir[1] = t3 - (2 * t2) + t1;
		factorsDir[2] = -(2 * t3) + (3 * t2);
		factorsDir[3] = t3 - t2;
	}

	SplineNode3D node;

	node.Pos += (Node0.Pos * factorsPos[0]);
	node.Pos += (Node0.Dir * factorsPos[1]);
	node.Pos += (Node1.Pos * factorsPos[2]);
	node.Pos += (Node1.Dir * factorsPos[3]);

	node.Dir += (Node0.Pos * factorsDir[0]);
	node.Dir += (Node0.Dir * factorsDir[1]);
	node.Dir += (Node1.Pos * factorsDir[2]);
	node.Dir += (Node1.Dir * factorsDir[3]);

	return node;
}



//	Bernstein / Bezier	???
SplineNode3D SplineSegment3D::Interpolate0(float t) const
{
	LInter linter;
	linter.SetT0(t);

	Point3D p[4]
	{
		(Prev -> Node0).Pos,
		Node0.Pos,
		Node1.Pos,
		(Next -> Node1).Pos,
	};

	float factorPos[4]
	{
		linter.GetT1() * linter.GetT1() * linter.GetT1(),
		linter.GetT0() * linter.GetT1() * linter.GetT1(),
		linter.GetT0() * linter.GetT0() * linter.GetT1(),
		linter.GetT0() * linter.GetT0() * linter.GetT0(),
	};
	//factorPos[1] *= 3;
	//factorPos[2] *= 3;

	Factors<float> factorDir = Factors_T_Something(t);
	Factors<float> TBC = Factors_TBC(T, B, C);

	Point3D dir[2]
	{
		((p[1] - p[0]) * TBC[0]) + ((p[2] - p[1]) * TBC[1]),
		((p[2] - p[1]) * TBC[2]) + ((p[3] - p[2]) * TBC[3]),
	};
	/*{
		(p[1] - p[0]) + (p[2] - p[1]),
		(p[2] - p[1]) + (p[3] - p[2]),
	};*/

	Point3D vals[4]
	/*{
		p[1],
		p[1] + (dir[0] / 3),
		p[2] - (dir[1] / 3),
		p[2],
	};*/
	{
		(p[1]),
		(p[1] * 3) + (dir[0] / 2),
		(p[2] * 3) - (dir[1] / 2),
		(p[2]),
	};

	SplineNode3D node;

	node.Pos = node.Pos + (vals[0] * factorPos[0]);
	node.Pos = node.Pos + (vals[1] * factorPos[1]);
	node.Pos = node.Pos + (vals[2] * factorPos[2]);
	node.Pos = node.Pos + (vals[3] * factorPos[3]);

	node.Dir = node.Dir + (vals[0] * factorDir[0]);
	node.Dir = node.Dir + (vals[1] * factorDir[1]);
	node.Dir = node.Dir + (vals[2] * factorDir[2]);
	node.Dir = node.Dir + (vals[3] * factorDir[3]);
	(void)factorDir;

	//node.Dir = (dir[0] * linter.GetT1()) + (dir[1] * linter.GetT0());

	return node;
}



SplineNode3D SplineSegment3D::Interpolate1(float t) const
{
	LInter linter;
	linter.SetT0(t);

	Point3D p[4]
	{
		(Prev -> Node0).Pos,
		Node0.Pos,
		Node1.Pos,
		(Next -> Node1).Pos,
	};

	float factorPos[4]
	{
		linter.GetT1() * linter.GetT1() * linter.GetT1(),
		linter.GetT0() * linter.GetT1() * linter.GetT1(),
		linter.GetT0() * linter.GetT0() * linter.GetT1(),
		linter.GetT0() * linter.GetT0() * linter.GetT0(),
	};
	factorPos[1] *= 3;
	factorPos[2] *= 3;

	Factors<float> factorDir = Factors_T_Something(t);

	Factors<float> TBC = Factors_TBC(T, B, C);

	Point3D dir[2]
	/*{
		((p[1] - p[0]) * TBC[0]) + ((p[2] - p[1]) * TBC[1]),
		((p[2] - p[1]) * TBC[2]) + ((p[3] - p[2]) * TBC[3]),
	};*/
	{
		(p[1] - p[0]) + (p[2] - p[1]),
		(p[2] - p[1]) + (p[3] - p[2]),
	};

	Point3D vals[4]
	{
		p[1],
		p[1] + (dir[0] / 3),
		p[2] - (dir[1] / 3),
		p[2],
	};
	/*{
		(p[1]),
		(p[1] * 3) + (dir[0] / 2),
		(p[2] * 3) - (dir[1] / 2),
		(p[2]),
	};*/

	SplineNode3D node;

	node.Pos = node.Pos + (vals[0] * factorPos[0]);
	node.Pos = node.Pos + (vals[1] * factorPos[1]);
	node.Pos = node.Pos + (vals[2] * factorPos[2]);
	node.Pos = node.Pos + (vals[3] * factorPos[3]);

	node.Dir = node.Dir + (vals[0] * factorDir[0]);
	node.Dir = node.Dir + (vals[1] * factorDir[1]);
	node.Dir = node.Dir + (vals[2] * factorDir[2]);
	node.Dir = node.Dir + (vals[3] * factorDir[3]);

	node.Dir = (dir[0] * linter.GetT1()) + (dir[1] * linter.GetT0());

	return node;
}

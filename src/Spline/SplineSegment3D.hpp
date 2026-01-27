#ifndef  SPLINE_SEGMENT_3D_HPP
# define SPLINE_SEGMENT_3D_HPP

# include "SplineNode3D.hpp"
# include "Factors.hpp"

# include "ValueType/LInter.hpp"

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

struct SplineSegment3D
{
	SplineNode3D	Node0;
	SplineNode3D	Node1;
	SplineSegment3D *	Prev;
	SplineSegment3D *	Next;

	float	T;	//Tension
	float	B;	//Bias
	float	C;	//Continuity

	SplineSegment3D()
	{ }
	SplineSegment3D(SplineNode3D node0, SplineNode3D node1, float t, float c, float b)
	{
		Node0 = node0;
		Node1 = node1;
		Prev = NULL;
		Next = NULL;

		T = t;
		C = c;
		B = b;
	}

	SplineNode3D	Calculate(float t) const
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
	SplineNode3D	CalculateLerp(float t) const
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
};

#endif
#ifndef  RAY_F2_HPP
# define RAY_F2_HPP

# include "ValueType/Vector/F2.hpp"

struct LineF2;

struct RayF2
{
	public:
	VectorF2	Pos;
	VectorF2	Dir;

	public:
	~RayF2() = default;
	RayF2() = default;
	RayF2(const RayF2 & other) = default;
	RayF2 & operator=(const RayF2 & other) = default;

	RayF2(const VectorF2 & pos, const VectorF2 & dir);
	RayF2(const LineF2 & line);

	VectorF2	ToPoint(float scalar) const;
	LineF2		ToLine(float scalar) const;
	LineF2		ToLine(float scalar0, float scalar1) const;

	VectorF2	Normal() const;

//	public:
//	class Interval
//	{
//		public:
//		const RayF2 & Ray;
//		const float Inter;
//		const int Index;
//		public:
//		Interval(const RayF2 & ray, float inter, int index);
//		public:
//		VectorF2 ToPoint() const;
//	};
//
//	public:
//	Interval Ray_Point(VectorF2 p);
};

#endif
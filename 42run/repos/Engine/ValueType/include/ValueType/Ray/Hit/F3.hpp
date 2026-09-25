#ifndef  RAY_HIT_F3_HPP
# define RAY_HIT_F3_HPP

struct RayF3;
struct VectorF3;

struct RayHitF3
{
	public:
	const RayF3 *	Ray = nullptr; // just store a ray ?
	float			Interval;

	public:
	bool	Is() const; // use NaN

	public:
	VectorF3	Pos() const;

	public:
	~RayHitF3() = default;
	RayHitF3() = default;
	RayHitF3(const RayHitF3 & other) = default;
	RayHitF3 & operator=(const RayHitF3 & other) = default;

	public:
	RayHitF3(const RayF3 & ray, float interval);

	public:
	bool	Consider(const RayHitF3 & other);
};

#endif
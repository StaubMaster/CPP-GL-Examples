#ifndef  RANGE_F_HPP
# define RANGE_F_HPP

struct RangeF
{
	private:
	float	Min = 0.0f;
	float	Len = 0.0f;
	float	Max = 0.0f;

	public:
	~RangeF() = default;
	RangeF() = default;
	RangeF(const RangeF & other) = default;
	RangeF & operator=(const RangeF & other) = default;

	public:
	RangeF(float min, float max);

	public:
	float	GetMin() const;
	float	GetMax() const;

	public:
	void	SetMin(float min);
	void	SetMax(float max);

	public:
	float	Length() const;
	void	MinLength(float len);
	void	MaxLength(float len);
};

#endif
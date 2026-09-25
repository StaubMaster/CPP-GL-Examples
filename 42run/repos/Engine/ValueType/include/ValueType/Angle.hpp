#ifndef  ANGLE_HPP
# define ANGLE_HPP

//# define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
//# define TAU 6.28318530717958647692528676655900576839433879875021164194988918461563281257241799725606965068423413

struct VectorF2;

struct Angle
{
	public:
	static constexpr float Pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f;
	static constexpr float Tau = 6.28318530717958647692528676655900576839433879875021164194988918461563281257241799725606965068423413f;
	// Tau = Pi * 2.0f;

	static constexpr float Full = Tau;
	static constexpr float Half = Pi;
	static constexpr float Quad = Pi * 0.5f;



	private:
	float	Value = 0.0f;



	public:
	~Angle() = default;
	Angle() = default;
	Angle(const Angle & other) = default;
	Angle & operator=(const Angle & other) = default;



	private:
	static float	DegreesToRadians(float val);
	static float	RadiansToDegrees(float val);

	Angle(float val);

	public:
	static Angle	Radians(float val);
	static Angle	Degrees(float val);
	static Angle	Section(float val);

	static Angle	PointToX(VectorF2 dir);
	static Angle	PointToY(VectorF2 dir);

	float	ToRadians() const;
	float	ToDegrees() const;



	public:
	void	clampPI();

	Angle	round(Angle size) const;
	Angle	roundC(Angle size) const;
	Angle	roundF(Angle size) const;



	public:
	float	Sin() const;
	float	Cos() const;
	float	Tan() const;

	static Angle	aSin(float val);
	static Angle	aCos(float val);
	static Angle	aTan2(float y, float x);



	public:
	void	forward(float & x, float & y) const;
	void	reverse(float & x, float & y) const;

	VectorF2	forward(VectorF2 p) const;
	VectorF2	reverse(VectorF2 p) const;



	public:
	Angle		operator+() const;
	Angle		operator-() const;

	Angle		operator+(const Angle & other) const;
	Angle		operator-(const Angle & other) const;
	Angle		operator*(const Angle & other) const;
	Angle		operator/(const Angle & other) const;

	Angle &		operator+=(const Angle & other);
	Angle &		operator-=(const Angle & other);
	Angle &		operator*=(const Angle & other);
	Angle &		operator/=(const Angle & other);



	Angle &		operator*=(float f);
	Angle &		operator/=(float f);
};

Angle	operator*(Angle a, float f);
Angle	operator/(Angle a, float f);

Angle	operator*(float f, Angle a);
Angle	operator/(float f, Angle a);

#endif
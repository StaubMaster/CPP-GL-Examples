#ifndef  L_INTER_HPP
# define L_INTER_HPP

/*
Linear Interpolator
put this into the Interpolator Example stuff ?
inherit from a generic Interpolator ?

but sometimes this is used in Shaders
but also sometimes, Shaders use more complex Interpolators
like quadratic and cubic

also they could use Splines and Bazier

just keep this like this for now until the other stuff gets improved
*/
struct LInter
{
	private:
	float _T0 = 0.0f;
	float _T1 = 0.0f;

	public:
	~LInter() = default;
	LInter() = default;
	LInter(const LInter & other) = default;
	LInter & operator=(const LInter & other) = default;

	private:
	LInter(float t0, float f1);

	public:
	static LInter	T0();
	static LInter	T1();

	public:
	float	GetT0() const;
	float	GetT1() const;

	public:
	void	SetT0(float val);
	void	SetT1(float val);

	public:
	float	Interpolate(float val0, float val1);
};

#endif
#ifndef  CUBIC_SPLINE_CURVE_3D_HPP
# define CUBIC_SPLINE_CURVE_3D_HPP

# include "InterPolator3D.hpp"
# include "CubicSpline3D.hpp"
# include "Generics/Container/Array.hpp"

class CubicSplineCurve3D : public InterPolator3D
{
	private:
	bool	Loop;
	public:
	Container::Array<VectorF3>		Nodes;
	Container::Array<CubicSpline3D>	Segments;

	public:
	~CubicSplineCurve3D();
	CubicSplineCurve3D();
	CubicSplineCurve3D(const CubicSplineCurve3D & other);
	CubicSplineCurve3D & operator=(const CubicSplineCurve3D & other);

	private:
	unsigned int	SegmentIndex(float & t);
	public:
	VectorF3 InterPolatePos(float t) override;
	VectorF3 InterPolateDir(float t) override;

	private:
	VectorF3 *	PrevNodePointer(unsigned int idx);
	VectorF3 *	NextNodePointer(unsigned int idx);

	private:
	void	ChangePrevPole1(unsigned int idx, VectorF3 pos, VectorF3 dir);
	void	ChangeNextPole0(unsigned int idx, VectorF3 pos, VectorF3 dir);

	public:
	void FiniteDifference();
	//void CatmullRom(float Tk);
	//void Cardinal(float ck);
	void KochanekBartels(CubicSpline3D::FactorsTCB tcb);
};

#endif
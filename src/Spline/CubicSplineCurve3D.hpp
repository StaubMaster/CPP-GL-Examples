#ifndef  CUBIC_SPLINE_CURVE_3D_HPP
# define CUBIC_SPLINE_CURVE_3D_HPP

# include "InterPolator3D.hpp"
# include "CubicSpline3D.hpp"
# include "Miscellaneous/Container/Array.hpp"

class CubicSplineCurve3D : public InterPolator3D
{
	private:
	bool	Loop;
	public:
	Container::Array<Point3D>		Nodes;
	Container::Array<CubicSpline3D>	Segments;

	public:
	~CubicSplineCurve3D();
	CubicSplineCurve3D();
	CubicSplineCurve3D(const CubicSplineCurve3D & other);
	CubicSplineCurve3D & operator=(const CubicSplineCurve3D & other);

	private:
	unsigned int	SegmentIndex(float & t);
	public:
	Point3D InterPolatePos(float t) override;
	Point3D InterPolateDir(float t) override;

	private:
	Point3D *	PrevNodePointer(unsigned int idx);
	Point3D *	NextNodePointer(unsigned int idx);

	private:
	void	ChangePrevPole1(unsigned int idx, Point3D pos, Point3D dir);
	void	ChangeNextPole0(unsigned int idx, Point3D pos, Point3D dir);

	public:
	void FiniteDifference();
	//void CatmullRom(float Tk);
	//void Cardinal(float ck);
	//void KochanekBartels(FactorsTCB tcb);
};

#endif
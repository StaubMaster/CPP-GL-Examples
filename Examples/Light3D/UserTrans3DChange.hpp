#ifndef  USER_TRANS_3D_CHANGE_HPP
# define USER_TRANS_3D_CHANGE_HPP

# include "ValueType/Ray3D.hpp"
# include "ValueType/Trans3D.hpp"

# include "ValueType/Vector/F3.hpp"
# include "PolyHedraUI/Object.hpp"

struct UserTrans3DChange
{
	UserTrans3DChange();



	enum class EIndicatorType
	{
		None,
		MoveAxisX,
		MoveAxisY,
		MoveAxisZ,
		SpinRingX,
		SpinRingY,
		SpinRingZ,
	};
	EIndicatorType	IndicatorHovering;
	Trans3D			IndicatorOffset;

	PolyHedraUIObject	MoveAxisXIndicator;
	PolyHedraUIObject	MoveAxisYIndicator;
	PolyHedraUIObject	MoveAxisZIndicator;

	PolyHedraUIObject	SpinRingXIndicator;
	PolyHedraUIObject	SpinRingYIndicator;
	PolyHedraUIObject	SpinRingZIndicator;

	void	FindIndicator(const Ray3D & ray);
	void	UpdateIndicator(float scale);



	enum class EChangeType
	{
		None,
		LineX,
		LineY,
		LineZ,
		PlaneX,
		PlaneY,
		PlaneZ,
		SpinX,
		SpinY,
		SpinZ,
	};
	EChangeType		ChangeType;

	bool	TypeIsNone() const;
	void	TypeUseNone();
	void	TypeUseL();
	void	TypeUseR();



	VectorF3	AxisX;
	VectorF3	AxisY;
	VectorF3	AxisZ;

	Trans3D		Trans;
	Trans3D		Offset;

	VectorF3		NewPosAxis(const Ray3D & ray, const VectorF3 & axis) const;
	VectorF3		NewPosPlane(const Ray3D & ray, const VectorF3 & axis) const;
	EulerAngle3D	NewRotPlaneX(const Ray3D & ray) const;
	Trans3D			NewTrans(const Ray3D & ray) const;
};

#endif
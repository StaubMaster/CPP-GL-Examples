#ifndef  USER_TRANS_3D_CHANGE_HPP
# define USER_TRANS_3D_CHANGE_HPP

# include "ValueType/Ray3D.hpp"
# include "ValueType/Trans3D.hpp"

# include "ValueType/Vector/F3.hpp"
# include "PolyHedraUI/Object.hpp"

# include "ValueType/View3D.hpp"
# include "Display/DisplaySize.hpp"

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
	void	UpdateIndicator(const View3D & view, const DisplaySize & display_size);



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

	Trans3D		Trans;
	Trans3D		Offset;

	VectorF3		NewPosAxis(const Ray3D & ray, const VectorF3 & axis) const;
	VectorF3		NewPosPlane(const Ray3D & ray, const VectorF3 & axis) const;
	EulerAngle3D	NewRotPlaneX(const Ray3D & ray) const;
	EulerAngle3D	NewRotPlaneY(const Ray3D & ray) const;
	EulerAngle3D	NewRotPlaneZ(const Ray3D & ray) const;
	Trans3D			NewTrans(const Ray3D & ray) const;
};

#endif
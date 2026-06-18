#ifndef  USER_TRANS_3D_CHANGE_HPP
# define USER_TRANS_3D_CHANGE_HPP

# include "ValueType/Ray3D.hpp"
# include "ValueType/Trans3D.hpp"
# include "ValueType/View3D.hpp"

# include "ValueType/Vector/F3.hpp"
# include "PolyHedraUI/Object.hpp"

struct UserTrans3DChange
{
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
	VectorF3		IndicatorOffset;

	PolyHedraUIObject	MoveAxisXIndicator;
	PolyHedraUIObject	MoveAxisYIndicator;
	PolyHedraUIObject	MoveAxisZIndicator;

	PolyHedraUIObject	SpinRingXIndicator;
	PolyHedraUIObject	SpinRingYIndicator;
	PolyHedraUIObject	SpinRingZIndicator;

	void FindIndicator(const Ray3D & ray);
	void UpdateIndicator(const View3D & view);



	enum class EChangeType
	{
		None,
		AxisX,
		AxisY,
		AxisZ,
		PlaneX,
		PlaneY,
		PlaneZ,
	};
	EChangeType		ChangeType;

	VectorF3	AxisX;
	VectorF3	AxisY;
	VectorF3	AxisZ;

	Trans3D		Trans;

	VectorF3	Offset;

	UserTrans3DChange();

	bool TypeIsNone() const;
	void TypeUseNone();
	void TypeUseL();
	void TypeUseR();

	Trans3D NewTransAxis(const Ray3D & ray, const VectorF3 & axis) const;
	Trans3D NewTransPlane(const Ray3D & ray, const VectorF3 & axis) const;
	Trans3D NewTrans(const Ray3D & ray);
};

#endif
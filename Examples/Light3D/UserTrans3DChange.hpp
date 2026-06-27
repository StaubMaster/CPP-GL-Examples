#ifndef  USER_TRANS_3D_CHANGE_HPP
# define USER_TRANS_3D_CHANGE_HPP

# include "ValueType/Ray/F3.hpp"
# include "ValueType/Trans/3D.hpp"

# include "ValueType/Vector/F3.hpp"
# include "PolyHedraUI/Object.hpp"

# include "ValueType/View/3D.hpp"
# include "Display/DisplaySize.hpp"

struct UserTrans3DChange
{
	UserTrans3DChange();



	PolyHedraUIObject	MoveAxisXIndicator;
	PolyHedraUIObject	MoveAxisYIndicator;
	PolyHedraUIObject	MoveAxisZIndicator;

	PolyHedraUIObject	SpinRingXIndicator;
	PolyHedraUIObject	SpinRingYIndicator;
	PolyHedraUIObject	SpinRingZIndicator;

	void	ShowIndicator();
	void	HideIndicator();

	void	FindIndicator(const RayF3 & ray);

	void	UpdateIndicatorColor();
	void	UpdateIndicatorScale(float scale);
	void	UpdateIndicatorTrans(const Trans3D & trans);

	void	UpdateIndicator(const Trans3D & trans, const View3D & view, const DisplaySize & display_size);



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
	EIndicatorType		HoveringType;
	bool				HoveringIsNone() const;
	Trans3D				HoveringOffset;

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
	EChangeType		SelectedType;
	bool			SelectedIsNone() const;
	Trans3D			SelectedOffset;



	void	UseNone();
	void	UseL();
	void	UseR();



	Trans3D		Trans;

	VectorF3		NewPosAxis(const RayF3 & ray, const VectorF3 & axis) const;
	VectorF3		NewPosPlane(const RayF3 & ray, const VectorF3 & axis) const;
	EulerAngle3D	NewRotPlaneX(const RayF3 & ray) const;
	EulerAngle3D	NewRotPlaneY(const RayF3 & ray) const;
	EulerAngle3D	NewRotPlaneZ(const RayF3 & ray) const;
	Trans3D			NewTrans(const RayF3 & ray) const;
};

#endif
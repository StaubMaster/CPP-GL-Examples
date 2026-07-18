#ifndef  USER_TRANS_3D_CHANGE_HPP
# define USER_TRANS_3D_CHANGE_HPP

# include "ValueType/Ray/F3.hpp"
# include "ValueType/Trans/3D.hpp"

# include "ValueType/Vector/F3.hpp"
//# include "PolyHedraUI/Object.hpp"
# include "NewPolyHedraDataType/TransScaleColor3D/Object.hpp"

# include "ValueType/View/3D.hpp"
# include "Display/DisplaySize.hpp"

/*
using this is a bit convoluted ?
take a Trans3D *
	dont show indicators if null
have a Update()
	change Trans
	round Trans
	change Indicators

make more members private
so changing is done with functions

make position and rotation changes seperate ?
*/

class DirectoryInfo;

struct UserTrans3DChange
{
	public:
	UserTrans3DChange();



	private:
	bool	IsVisible;

	//PolyHedraUIObject	MoveAxisX;
	//PolyHedraUIObject	MoveAxisY;
	//PolyHedraUIObject	MoveAxisZ;
	//PolyHedraUIObject	SpinRingX;
	//PolyHedraUIObject	SpinRingY;
	//PolyHedraUIObject	SpinRingZ;

	TransScaleColor3D::Object	MoveAxisX;
	TransScaleColor3D::Object	MoveAxisY;
	TransScaleColor3D::Object	MoveAxisZ;
	TransScaleColor3D::Object	SpinRingX;
	TransScaleColor3D::Object	SpinRingY;
	TransScaleColor3D::Object	SpinRingZ;

	// Center
	//  L: move along Plane perpendicular to View Ray
	//  R: rotate along Plane perpendicular to View Ray

	public:
	void	IndicatorsInit(const DirectoryInfo & dir);
	bool	IndicatorsIsVisible() const;
	void	IndicatorsShow();
	void	IndicatorsHide();

	void	IndicatorsFind(const RayF3 & ray);

	private:
	void	IndicatorsUpdateColor();
	void	IndicatorsUpdateScale(float scale);
	void	IndicatorsUpdateTrans();

	public:
	void	IndicatorsUpdate(const View3D & view, const DisplaySize & display_size);



	private:
	enum class EIndicatorType // EHoveringType
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
	Trans3D				HoveringOffset;

	public:
	void	HoveringMakeNone();
	bool	HoveringIsNone() const;



	private:
	enum class EChangeType // ESelectedType
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
	Trans3D			SelectedOffset;

	public:
	void	SelectedMakeNone();
	bool	SelectedIsNone() const;

	public:
	void	SelectedMakeL();
	void	SelectedMakeR();

	public:
	bool	IsIdle() const;



	private:
	Trans3D		Trans;

	public:
	Trans3D		GetTrans() const;
	void		SetTrans(Trans3D trans);

	private:
	VectorF3		CalcPosAxis(const RayF3 & ray, const VectorF3 & axis) const;
	VectorF3		CalcPosPlane(const RayF3 & ray, const VectorF3 & axis) const;
	EulerAngle3D	CalcRotPlaneX(const RayF3 & ray) const;
	EulerAngle3D	CalcRotPlaneY(const RayF3 & ray) const;
	EulerAngle3D	CalcRotPlaneZ(const RayF3 & ray) const;
	Trans3D			CalcTrans(const RayF3 & ray) const;

	public:
	void			NewTrans(const RayF3 & ray);
};

#endif
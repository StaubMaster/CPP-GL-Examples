#ifndef  CHANGE_3D_EULER_ANGLE_3D_HPP
# define CHANGE_3D_EULER_ANGLE_3D_HPP

# include "UI/Change3D/General/Base.hpp"

# include "ValueType/Vector/F3.hpp"
# include "ValueType/EulerAngle3D.hpp"

# include "Special/TransScaleColor3D/Display/Object.hpp"
# include "Special/TransScaleColor3D/Logical/Data.hpp"

namespace Change3D
{
struct EulerAngle3D : public Base
{
	private:
	bool	IsVisible = false;
	public:
	bool	IndicatorsIsVisible() const override;
	void	IndicatorsShow() override;
	void	IndicatorsHide() override;

	public:
	static TransScaleColor3D::DisplayObject *		SpinRingX_DisplayObject;
	static TransScaleColor3D::DisplayObject *		SpinRingY_DisplayObject;
	static TransScaleColor3D::DisplayObject *		SpinRingZ_DisplayObject;
	private:
	TransScaleColor3D::LogicalData			SpinRingX_Data;
	TransScaleColor3D::LogicalData			SpinRingY_Data;
	TransScaleColor3D::LogicalData			SpinRingZ_Data;
	public:
	void	IndicatorsDisplay() override;

	private:
	::VectorF3	Center;
	public:
	void	CenterChange(const ::VectorF3 & center);

	private:
	void	IndicatorsUpdateColor() override;
	void	IndicatorsUpdateScale(float scale) override;
	void	IndicatorsUpdateTrans() override;
	public:
	void	IndicatorsUpdate(const View3D & view, const DisplaySize & display_size) override;

	public:
	RayHitF3	IndicatorsFind(const RayF3 & ray) override;



	private:
	enum class EType
	{
		None,
		Other,
		Hovering_SpinRingX,
		Hovering_SpinRingY,
		Hovering_SpinRingZ,
		Selected_SpinX,
		Selected_SpinY,
		Selected_SpinZ,
	};
	EType	Type = EType::None;

	private:
	::EulerAngle3D		Offset;

	private:
	void	Make(EType type, ::EulerAngle3D offset);

	public:
	void	MakeNone() override;
	void	MakeOther() override;

	public:
	bool	IsNone() const override;
	bool	IsHovering() const override;
	bool	IsSelected() const override;

	public:
	void	MakeL() override;
	void	MakeR() override;



	private:
	::EulerAngle3D	Value;
	public:
	const ::EulerAngle3D &	Get() const;
	void					Set(const ::EulerAngle3D & val);

	private:
	::EulerAngle3D	CalculatePlaneX(const RayF3 & ray) const;
	::EulerAngle3D	CalculatePlaneY(const RayF3 & ray) const;
	::EulerAngle3D	CalculatePlaneZ(const RayF3 & ray) const;
	private:
	::EulerAngle3D	Calculate(const RayF3 & ray) const;

	public:
	void	ChangeValue(const RayF3 & ray) override;
};
};

#endif
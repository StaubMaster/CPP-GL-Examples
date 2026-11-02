#ifndef  CHANGE_3D_EULER_ANGLE_3D_HPP
# define CHANGE_3D_EULER_ANGLE_3D_HPP

# include "Base.hpp"

# include "ValueType/Vector/F3.hpp"
# include "ValueType/EulerAngle3D.hpp"

//# include "Special/TransScaleColor3D/Object.hpp"
# include "Special/TransScaleColor3D/Display/Object.hpp"
# include "Special/TransScaleColor3D/Logical/Data.hpp"

namespace Change3D
{
struct EulerAngle3D : public Base
{
	private:
	//TransScaleColor3D::Object				SpinRingX;
	//TransScaleColor3D::Object				SpinRingY;
	//TransScaleColor3D::Object				SpinRingZ;
	TransScaleColor3D::DisplayObject *		SpinRingX_DisplayObject = nullptr;
	TransScaleColor3D::DisplayObject *		SpinRingY_DisplayObject = nullptr;
	TransScaleColor3D::DisplayObject *		SpinRingZ_DisplayObject = nullptr;
	TransScaleColor3D::LogicalData			SpinRingX_Data;
	TransScaleColor3D::LogicalData			SpinRingY_Data;
	TransScaleColor3D::LogicalData			SpinRingZ_Data;

	public:
	::VectorF3	Center;

	public:
	void	IndicatorsInit(PolyHedraManager & manager, const DirectoryInfo & dir) override;

	private:
	bool	IsVisible = false;
	public:
	bool	IndicatorsIsVisible() const override;
	void	IndicatorsShow() override;
	void	IndicatorsHide() override;

	public:
	RayHitF3	IndicatorsFind(const RayF3 & ray) override;

	private:
	void	IndicatorsUpdateColor() override;
	void	IndicatorsUpdateScale(float scale) override;
	void	IndicatorsUpdateTrans() override;

	public:
	void	IndicatorsUpdate(const View3D & view, const DisplaySize & display_size) override;



	private:
	::EulerAngle3D	Value;

	public:
	const ::EulerAngle3D &	Get() const;
	void					Set(const ::EulerAngle3D & val);

	private:
	void	RoundValue() override;
	public:
	void	ChangeValue(const RayF3 & ray) override;



	private:
	enum class EIndicatorType // EHoveringType
	{
		None,
		Other,
		SpinRingX,
		SpinRingY,
		SpinRingZ,
	};
	EIndicatorType		HoveringType = EIndicatorType::None;
	::EulerAngle3D		HoveringOffset;

	public:
	bool	HoveringIsNone() const override;
	void	HoveringMakeNone() override;
	void	HoveringMakeOther() override;



	private:
	enum class EChangeType // ESelectedType
	{
		None,
		SpinX,
		SpinY,
		SpinZ,
	};
	EChangeType		SelectedType = EChangeType::None;
	::EulerAngle3D	SelectedOffset;

	public:
	bool	SelectedIsNone() const  override;
	void	SelectedMakeNone()  override;

	public:
	void	SelectedMakeL() override;
	void	SelectedMakeR() override;



	private:
	::EulerAngle3D	CalculatePlaneX(const RayF3 & ray) const;
	::EulerAngle3D	CalculatePlaneY(const RayF3 & ray) const;
	::EulerAngle3D	CalculatePlaneZ(const RayF3 & ray) const;
	private:
	::EulerAngle3D	Calculate(const RayF3 & ray) const;



	public:
	void	Display() override;
};
};

#endif
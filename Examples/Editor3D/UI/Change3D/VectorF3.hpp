#ifndef  CHANGE_3D_VECTOR_F_3_HPP
# define CHANGE_3D_VECTOR_F_3_HPP

# include "Base.hpp"

# include "ValueType/Vector/F3.hpp"

# include "ValueType/Ray/F3.hpp"
# include "ValueType/Ray/Hit/F3.hpp"

# include "ValueType/View/3D.hpp"
# include "Display/DisplaySize.hpp"

# include "NewPolyHedra/DataType/TransScaleColor3D/Object.hpp"

class DirectoryInfo;

namespace Change3D
{
struct VectorF3 : public Base
{
	private:
	TransScaleColor3D::Object	MoveAxisX;
	TransScaleColor3D::Object	MoveAxisY;
	TransScaleColor3D::Object	MoveAxisZ;

	public:
	void	IndicatorsInit(const DirectoryInfo & dir) override;

	public:
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
	::VectorF3	Value;

	public:
	const ::VectorF3 &	Get() const;
	void				Set(const ::VectorF3 & val);

	private:
	void	RoundValue() override;
	public:
	void	ChangeValue(const RayF3 & ray) override;



	private:
	enum class EIndicatorType // EHoveringType
	{
		None, // none gray
		Other, // all gray
		MoveAxisX,
		MoveAxisY,
		MoveAxisZ,
	};
	EIndicatorType		HoveringType = EIndicatorType::None;
	::VectorF3			HoveringOffset;

	public:
	bool	HoveringIsNone() const override;
	void	HoveringMakeNone() override;
	void	HoveringMakeOther() override;
	void	HoveringMake(EIndicatorType type, ::VectorF3 offset);



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
	};
	// seperate L and R
	// seperate Enums, or seperate Changers ?
	// seperate Changers would mean duplicate Indicators
	EChangeType		SelectedType = EChangeType::None;
	::VectorF3		SelectedOffset;

	public:
	bool	SelectedIsNone() const override;
	void	SelectedMakeNone() override;

	public:
	void	SelectedMakeL() override;
	void	SelectedMakeR() override;



	private:
	::VectorF3	CalculateAxis(const RayF3 & ray, const ::VectorF3 & axis) const;
	::VectorF3	CalculatePlane(const RayF3 & ray, const ::VectorF3 & axis) const;
	private:
	::VectorF3	Calculate(const RayF3 & ray) const;
};
};

#endif
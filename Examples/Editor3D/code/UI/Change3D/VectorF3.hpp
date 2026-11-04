#ifndef  CHANGE_3D_VECTOR_F_3_HPP
# define CHANGE_3D_VECTOR_F_3_HPP

# include "Base.hpp"

# include "ValueType/Vector/F3.hpp"

# include "Special/TransScaleColor3D/Display/Object.hpp"
# include "Special/TransScaleColor3D/Logical/Data.hpp"

namespace Change3D
{
struct VectorF3 : public Base
{
	public:
	static TransScaleColor3D::DisplayObject *		MoveAxisX_DisplayObject;
	static TransScaleColor3D::DisplayObject *		MoveAxisY_DisplayObject;
	static TransScaleColor3D::DisplayObject *		MoveAxisZ_DisplayObject;

	private:
	TransScaleColor3D::LogicalData			MoveAxisX_Data;
	TransScaleColor3D::LogicalData			MoveAxisY_Data;
	TransScaleColor3D::LogicalData			MoveAxisZ_Data;

	private:
	bool	IsVisible = false;
	public:
	bool	IndicatorsIsVisible() const override;
	void	IndicatorsShow() override;
	void	IndicatorsHide() override;

	/*combine
		IndicatorsFind()
		ChangeValue()
	*/

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
	enum class EType
	{
		None, // none gray
		Other, // all gray
		Hovering_MoveAxisX,
		Hovering_MoveAxisY,
		Hovering_MoveAxisZ,
		Selected_LineX,
		Selected_LineY,
		Selected_LineZ,
		Selected_PlaneX,
		Selected_PlaneY,
		Selected_PlaneZ,
	};
	EType	Type = EType::None;

	::VectorF3		Offset;

	private:
	void	Make(EType type, ::VectorF3 offset);

	public:
	void	MakeNone() override;
	void	MakeOther() override;

	public:
	bool	IsNone() const override;
	bool	IsHovering() const override;
	bool	IsSelected() const override;

	public:
	void	SelectedMakeL() override;
	void	SelectedMakeR() override;



	private:
	::VectorF3	CalculateAxis(const RayF3 & ray, const ::VectorF3 & axis) const;
	::VectorF3	CalculatePlane(const RayF3 & ray, const ::VectorF3 & axis) const;
	private:
	::VectorF3	Calculate(const RayF3 & ray) const;



	public:
	void	Display() override;
};
};

#endif
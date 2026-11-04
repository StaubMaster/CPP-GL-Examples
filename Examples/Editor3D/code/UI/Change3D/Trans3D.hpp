#ifndef  CHANGE_3D_TRANS_3D_HPP
# define CHANGE_3D_TRANS_3D_HPP

# include "Base.hpp"

# include "Generics/Container/Binary.hpp"

# include "UI/Change3D/VectorF3.hpp"
# include "UI/Change3D/EulerAngle3D.hpp"

namespace Change3D
{
// make Change3D::Collection
struct Trans3D : public Base
{
	Container::Binary<Base *>	Changes;

	~Trans3D() = default;
	Trans3D();
	Trans3D(const Trans3D & other) = delete;
	Trans3D & operator=(const Trans3D & other) = delete;

	Change3D::VectorF3		VectorF3;
	Change3D::EulerAngle3D	EulerAngle3D;

	public:
	bool	IndicatorsIsVisible() const override;
	void	IndicatorsHide() override;
	void	IndicatorsShow() override;

	private:
	Base *		Hovering = nullptr;
	public:
	RayHitF3	IndicatorsFind(const RayF3 & ray) override;

	private:
	void	IndicatorsUpdateColor() override;
	void	IndicatorsUpdateScale(float scale) override;
	void	IndicatorsUpdateTrans() override;

	public:
	void	IndicatorsUpdate(const View3D & view, const DisplaySize & display_size) override;



	private:
	void	RoundValue() override;
	public:
	void	ChangeValue(const RayF3 & ray) override;



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



	public:
	void	Display() override;
};
};

#endif
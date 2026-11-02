#ifndef  CHANGE_3D_TRANS_3D_HPP
# define CHANGE_3D_TRANS_3D_HPP

# include "Base.hpp"

# include "Generics/Container/Binary.hpp"

# include "UI/Change3D/VectorF3.hpp"
# include "UI/Change3D/EulerAngle3D.hpp"

namespace Change3D
{
struct Trans3D : public Base // make Change3D::Collection
{
	Container::Binary<Base *>	Changes;

	~Trans3D() = default;
	Trans3D();
	Trans3D(const Trans3D & other) = delete;
	Trans3D & operator=(const Trans3D & other) = delete;

	Change3D::VectorF3		VectorF3;
	Change3D::EulerAngle3D	EulerAngle3D;

	public:
	void	IndicatorsInit(PolyHedraManager & manager, const DirectoryInfo & dir) override;

	public:
	bool	IndicatorsIsVisible() const override;
	void	IndicatorsHide() override;
	void	IndicatorsShow() override;

	public:
	Base *	IndicatorsFind(const RayF3 & ray);

	private:
	void	IndicatorsUpdateColor() override;
	void	IndicatorsUpdateScale(float scale) override;
	void	IndicatorsUpdateTrans() override;

	public:
	void	IndicatorsUpdate(const View3D & view, const DisplaySize & display_size) override;

	public:
	bool	IsNone() const;

	public:
	bool	HoveringIsNone() const;
	void	HoveringMakeNone();
	void	HoveringMakeOther();

	public:
	bool	SelectedIsNone() const override;
	void	SelectedMakeNone() override;

	public:
	void	SelectedMakeL() override;
	void	SelectedMakeR() override;

	public:
	//void	SelectedMakeL(unsigned int idx);
	//void	SelectedMakeR(unsigned int idx);

	private:
	void	RoundValue() override;
	public:
	void	ChangeValue(const RayF3 & ray) override;



	public:
	void	Display();
};
};

#endif
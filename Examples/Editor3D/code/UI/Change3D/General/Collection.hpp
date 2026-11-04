#ifndef  CHANGE_3D_COLLECTION_HPP
# define CHANGE_3D_COLLECTION_HPP

# include "UI/Change3D/General/Base.hpp"

# include "Generics/Container/Binary.hpp"

namespace Change3D
{
struct Collection : public Base
{
	public:
	bool	IndicatorsIsVisible() const override;
	void	IndicatorsHide() override;
	void	IndicatorsShow() override;

	public:
	void	IndicatorsDisplay() override;

	private:
	void	IndicatorsUpdateColor() override;
	void	IndicatorsUpdateScale(float scale) override;
	void	IndicatorsUpdateTrans() override;

	public:
	void	IndicatorsUpdate(const View3D & view, const DisplaySize & display_size) override;

	private:
	Base *		Hovering = nullptr;
	public:
	RayHitF3	IndicatorsFind(const RayF3 & ray) override;



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



	protected:
	Container::Binary<Base *>	Changes;

	public:
	~Collection() = default;
	Collection();
	Collection(const Collection & other) = delete;
	Collection & operator=(const Collection & other) = delete;



	public:
	void	ChangeValue(const RayF3 & ray) override;
};
};

#endif
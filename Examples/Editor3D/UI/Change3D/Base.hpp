#ifndef  CHANGE_3D_BASE_HPP
# define CHANGE_3D_BASE_HPP

# include "ValueType/Ray/F3.hpp"
# include "ValueType/Ray/Hit/F3.hpp"

# include "ValueType/View/3D.hpp"
# include "Display/DisplaySize.hpp"

class DirectoryInfo;

namespace Change3D
{
struct Base
{
	private:
	bool	IsVisible = false;

	public:
	bool			IndicatorsIsVisible() const;
	virtual void	IndicatorsShow();
	virtual void	IndicatorsHide();
	virtual void	IndicatorsInit(const DirectoryInfo & dir) = 0;

	public:
	virtual RayHitF3	IndicatorsFind(const RayF3 & ray) = 0;

	private:
	virtual void	IndicatorsUpdateColor() = 0;
	virtual void	IndicatorsUpdateScale(float scale) = 0;
	virtual void	IndicatorsUpdateTrans() = 0;

	public:
	virtual void	IndicatorsUpdate(const View3D & view, const DisplaySize & display_size) = 0;



	public:
	bool	IsNone() const;
	void	MakeNone();

	public:
	virtual bool	HoveringIsNone() const = 0;
	virtual void	HoveringMakeNone() = 0;
	virtual void	HoveringMakeOther() = 0;

	public:
	virtual bool	SelectedIsNone() const = 0;
	virtual void	SelectedMakeNone() = 0;

	public:
	virtual void	SelectedMakeL() = 0;
	virtual void	SelectedMakeR() = 0;



	private:
	virtual void	RoundValue() = 0;
	public:
	virtual void	ChangeValue(const RayF3 & ray) = 0;
};
};

#endif
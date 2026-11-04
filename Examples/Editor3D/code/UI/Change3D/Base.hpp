#ifndef  CHANGE_3D_BASE_HPP
# define CHANGE_3D_BASE_HPP

# include "ValueType/Ray/F3.hpp"
# include "ValueType/Ray/Hit/F3.hpp"

# include "ValueType/View/3D.hpp"
# include "Display/DisplaySize.hpp"

class DirectoryInfo;
class PolyHedraManager;

struct RayHitF3;

namespace Change3D
{
struct Base
{
	public:
	virtual bool	IndicatorsIsVisible() const = 0;
	virtual void	IndicatorsShow() = 0;
	virtual void	IndicatorsHide() = 0;

	public:
	virtual RayHitF3	IndicatorsFind(const RayF3 & ray) = 0;

	private:
	virtual void	IndicatorsUpdateColor() = 0;
	virtual void	IndicatorsUpdateScale(float scale) = 0;
	virtual void	IndicatorsUpdateTrans() = 0;

	public:
	virtual void	IndicatorsUpdate(const View3D & view, const DisplaySize & display_size) = 0;



	public:
	virtual void	MakeNone() = 0;
	virtual void	MakeOther() = 0;

	public:
	virtual bool	IsNone() const = 0;
	virtual bool	IsHovering() const = 0;
	virtual bool	IsSelected() const = 0;

	public:
	virtual void	SelectedMakeL() = 0;
	virtual void	SelectedMakeR() = 0;



	private:
	virtual void	RoundValue() = 0;
	public:
	virtual void	ChangeValue(const RayF3 & ray) = 0;



	public:
	virtual void	Display() = 0; // move this up
};
};

#endif
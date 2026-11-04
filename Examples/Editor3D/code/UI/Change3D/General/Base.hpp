#ifndef  CHANGE_3D_BASE_HPP
# define CHANGE_3D_BASE_HPP

struct View3D;
struct DisplaySize;

class DirectoryInfo;
class PolyHedraManager;

struct RayF3;
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
	virtual void	IndicatorsDisplay() = 0; // DisplayPut

	private:
	virtual void	IndicatorsUpdateColor() = 0;
	virtual void	IndicatorsUpdateScale(float scale) = 0;
	virtual void	IndicatorsUpdateTrans() = 0;
	public:
	virtual void	IndicatorsUpdate(const View3D & view, const DisplaySize & display_size) = 0;

	public:
	virtual RayHitF3	IndicatorsFind(const RayF3 & ray) = 0;



	public:
	virtual void	MakeNone() = 0;
	virtual void	MakeOther() = 0;

	public:
	virtual bool	IsNone() const = 0;
	virtual bool	IsHovering() const = 0;
	virtual bool	IsSelected() const = 0;

	public:
	virtual void	MakeL() = 0;
	virtual void	MakeR() = 0;



	public:
	~Base() = default;
	Base() = default;
	Base(const Base & other) = delete;
	Base & operator=(const Base & other) = delete;



	/*combine
		IndicatorsFind()
		ChangeValue()
	*/
	public:
	virtual void	ChangeValue(const RayF3 & ray) = 0;
};
};

#endif
#ifndef  UI_CONTROL_WINDOW_HPP
# define UI_CONTROL_WINDOW_HPP

# include "Control/General/Control_UserRelay.hpp"
# include "Control/General/Control_Container.hpp"

# include "ValueType/_Include.hpp"

struct DisplaySize;

namespace UI
{
class Manager;
class Control_Base;
namespace Control_
{
class Form;
class Window : public Control_Container, public Control_UserRelay
{
	public:
	UI::Manager *			Manager_ = nullptr;



	public:
	void	ChildClear() override;
	void	ChildRemove(Control_Base & control) override;
	void	ChildInsert(Control_Base & control) override;

	private:
	bool				Check(const DisplayPosition & display_pos) const override;
	UI::Control_Base *	Find(const DisplayPosition & display_pos) override;

	private:
	UI::Control_Base *	Hovering_ = nullptr;
	UI::Control_Base *	Selected_ = nullptr;
	public:
	UI::Control_Base *	Hovering() const;
	UI::Control_Base *	Selected() const;
	private:
	void	HoveringChange(UI::Control_Base * control, const DisplayPosition & display_pos);
	void	SelectedChange();
	public:
	void	HoveringUpdate(const DisplayPosition & display_pos);
	void	SelectedUpdate();



	private:	VectorF2	Size;
	public:		void		SizeChange(const DisplaySize & display_size);
	public:		BoxF2		Box() const;



	private:	bool	DepthCalculateIsRequested = false;
	public:		void	DepthCalculateRequest();
//	public:		void	DepthCalculateResolve();
	private:	void	DepthCalculate();

	private:	unsigned int	LayerCount = 0;
	private:	float			LayerDepth_ = 0.0f;
	public:		float			LayerDepth() const;
	public:		float	Depth(float depth = 0.0f) const;



	public:
	void	DisplayPut();
	public:
	void	Update();



	public:
	~Window() = default;
	Window();



	public:
	void	RelayMove(MoveArgs args);
	void	RelayHover(HoverArgs args) override;
	void	RelayClick(ClickArgs args) override;
	void	RelayScroll(ScrollArgs args) override;
	void	RelayDrag(DragArgs args) override;
	void	RelayKey(KeyArgs args) override;
	void	RelayText(TextArgs args) override;
};
};
};

#endif
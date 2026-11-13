#ifndef  UI_CONTROL_WINDOW_HPP
# define UI_CONTROL_WINDOW_HPP

# include "Control/General/Control_UserRelay.hpp"
# include "Control/General/Control_Container.hpp"

# include "ValueType/_Include.hpp"

struct DisplaySize;

namespace UI
{
class Manager;
namespace Control
{
class Form;
class Window : public Control_Container<Form>, public Control_UserRelay
{
	public:
	UI::Manager *			Manager_ = nullptr;



	public:
	void	ChildClear() override;
	void	ChildRemove(Form & control) override;
	void	ChildInsert(Form & control) override;

	private:
	bool					Check(const DisplayPosition & display_pos) const override;
	UI::Control::Form *		Find(const DisplayPosition & display_pos) override;

	private:
	UI::Control::Form *		Hovering_ = nullptr;
	UI::Control::Form *		Selected_ = nullptr;
	public:
	UI::Control::Form *		Hovering() const;
	UI::Control::Form *		Selected() const;
	private:
	void	HoveringChange(UI::Control::Form * form, const DisplayPosition & display_pos);
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
	private:	float			LayerDepth = 0.0f;
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
#ifndef  UI_CONTROL_FORM_HPP
# define UI_CONTROL_FORM_HPP

# include "Control/General/Control_Display.hpp"
# include "Control/General/Control_UserRelay.hpp"
# include "Control/General/Control_Container.hpp"

/*	TODO
dont overlap with other Forms
	eighter completely behind another or infront of another
	have a seperate draw call for each form ?
movable
	bool isMovable
resizable
	like window,
	bool resizableX
	bool resizableY
*/

/* ControlBar
	X Button in Top Right to "close" Form
	the Top Bar in general is used to move
		currently any part of the Form, except those used for resizing, are used for moving

	make Optional ?
	area for Children should not include Bar
	BoxBoarder is different not default
	BoxContent is determined calculated from BoxBoarder
	override BoxUpdate
*/

namespace UI
{
class Manager;
namespace Control
{
class Window;
class Base;
class Form : public Control_Container<Base>, public Control_Display, public Control_UserRelay
{
	public:
	UI::Control::Window *	Window_ = nullptr;

	public:
			UI::Manager *			_Manager();
			UI::Manager *			_Manager() const;



	public:
	void	ChildClear() override;
	void	ChildRemove(Base & control) override;
	void	ChildInsert(Base & control) override;

	public:
	bool					Check(const DisplayPosition & display_pos) const override;
	UI::Control::Base *		Find(const DisplayPosition & display_pos) override;

	private:
	UI::Control::Base *		Hovering_ = nullptr;
	UI::Control::Base *		Selected_ = nullptr;
	public:
	UI::Control::Base *		Hovering() const;
	UI::Control::Base *		Selected() const;
	public:
	void	HoveringChange(UI::Control::Base * control, const DisplayPosition & display_pos);
	void	SelectedChange();
	public:
	void	HoveringUpdate(const DisplayPosition & display_pos);
	void	SelectedUpdate();



	public:
	bool	IsVisible() const override;
	void	Show() override;
	void	Hide() override;



	public:		unsigned int	Layer() const override;

	public:		unsigned int	LayerLimit() const override;

	private: public:	float	Depth_ = 0.0f;
	public:		void	DepthChange(float depth);
	public:		float	Depth(float depth = 0.0f) const override;



	protected:	virtual	void	AnchorUpdate() override;

	protected:
	bool	MetaIs() const override;
	BoxF2	MetaBoxBoarder() const override;
	BoxF2	MetaBoxContent() const override;

	private:		void	AutoAnchorUpdate_Y_StackMin() override;

	public:
	virtual ColorF4		Color() const override;



	protected:	virtual	void	DisplayPut() const override;
	public:				void	DisplayPutRecursive() const override;



	protected:	virtual	void	DisplayUpdate() override;



	public:				void	UpdateRecursive() override;



	public:
	virtual ~Form() = default;
	Form();

	public:
	bool	IsMovable = false;
	bool	IsResizable = false;
	//BoxF2	SizeLimit;



	private:
	enum class EBoxChangeType : unsigned char
	{
		None,
		Move,
		ResizeMinX,
		ResizeMaxX,
		ResizeMinY,
		ResizeMaxY,
		ResizeMinMin,
		ResizeMinMax,
		ResizeMaxMin,
		ResizeMaxMax,
	};

	private:
	EBoxChangeType	FindChangingArea(VectorF2 mouse) const;
	EBoxChangeType	ChangingBoxType;
	BoxF2			ChangingBoxRel;

	private:
	void	ChangeAnchorBox(BoxF2 box, EBoxChangeType type);

	public:
	void	RelayHover(HoverArgs args) override;
	void	RelayDrag(DragArgs args) override;
};
};
};

#endif
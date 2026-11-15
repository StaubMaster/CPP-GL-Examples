#ifndef  UI_CONTROL_FORM_HPP
# define UI_CONTROL_FORM_HPP

# include "Control/General/Control_Base.hpp"

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

/* make Form a Control (again)
*/

namespace UI
{
class Manager;
namespace Control_
{
class Window;
class Base;
class Form : public Control_Base
{
	public:
	UI::Control_::Window *	Window_ = nullptr;

	public:
			UI::Manager *			_Manager();
			UI::Manager *			_Manager() const;



	public:
	void	ChildClear() override;
	void	ChildRemove(Control_Base & control) override;
	void	ChildInsert(Control_Base & control) override;

	public:
	bool					Check(const DisplayPosition & display_pos) const override;
	UI::Control_Base *		Find(const DisplayPosition & display_pos) override;

	private:
	UI::Control_Base *		Hovering_ = nullptr;
	UI::Control_Base *		Selected_ = nullptr;
	public:
	UI::Control_Base *		Hovering() const;
	UI::Control_Base *		Selected() const;
	public:
	void	HoveringChange(UI::Control_Base * control, const DisplayPosition & display_pos);
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

	private: public:	float	DepthOffset_ = 0.0f;
	public:		void	DepthChange(float depth);
	public:		float	LayerDepth() const override;
	public:		float	DepthOffset() const override;
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
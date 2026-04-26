#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

#include "Data.hpp"

#include "Anchor2D.hpp"

#include "User/MouseArgs.hpp"
#include "User/KeyBoardArgs.hpp"

#include "ValueType/_Include.hpp"

#include "Miscellaneous/Container/Binary.hpp"

#include "Object.hpp"

#include "AnchorEnum.hpp"

namespace UI
{
namespace Text { class Manager; };
namespace Control
{
class Manager;
class Base
{
	protected:
	Manager *			ControlManager;
	UI::Text::Manager *	TextManager;

	protected:
	Object		ControlObject;

	protected:
	Base * Parent;
	Container::Binary<Control::Base *> Children;

	public:
	float			Layer;

	protected:
	bool	_Enabled;	//visible but cannot be interacted with by User, can be changed via code, Grayed out ?
	public:
	bool	IsEnabled() const;
	void	MakeEnabled();
	void	MakeDisabled();

	protected:
	bool	_Visible;	//is current and children visible
	public:
	bool	IsVisible() const;
	void	Show();
	void	Hide();

	protected:
	bool	_Opaque;	//is current invisible, does not effect children
	public:
	bool	IsTransparent() const;
	bool	IsOpaque() const;
	void	MakeTransparent();
	void	MakeOpaque();

	public:
	bool	Drawable() const;		//should this currently be drawn ?
	bool	Interactible() const;	//can be interacted with

	public:
	bool			Deletable;		//should be deleted when Parent is deleted

	protected:
	Point2D			AnchorSize;
	Point2D			AnchorNormal;
	AxisBox2D		AnchorDist;
	AxisBox2D		AnchorPadding;

	public:
	Anchor2D		Anchor;

	AxisBox2D		AnchorBox;
	protected:
	bool			AnchorBoxChanged;

	public:
	ColorF4			ColorDefault;
	//Color			ColorDisabled;
	ColorF4			ColorHover;
	bool			ColorChanged;

	public:
	Base();
	virtual ~Base();

	public:
	void ChildInsert(Base & control);
	void ChildInsert(Base * control);
	virtual void ChangeManager(Manager * manager);
	virtual void ChangeManager(UI::Text::Manager * manager);

	//	for automatic Updating. should not be called by User
	public:
	void UpdateEntrys();

	//	for automatic Updating. should not be called by User
	private:
	void UpdateDrawable();
	void InsertDrawingEntry();
	void RemoveDrawingEntry();

	//	for automatic Updating. should not be called by User
	public:
	void UpdateBox();

	//	for automatic Updating. should not be called by User
	public:
	Base * CheckHover(Point2D mouse);

	//	for automatic Updating. should not be called by User
	public:
	void HoverEnter();
	void HoverLeave();

	//	Relay Auto
	protected:
	virtual void UpdateEntryAnchorBoxRelay();
	virtual void UpdateEntryColorRelay();
	virtual void UpdateEntrysRelay();

	virtual void InsertDrawingEntryRelay();
	virtual void RemoveDrawingEntryRelay();
	virtual void UpdateBoxRelay();

	//	Relay User
	public:
	virtual void RelayHover(unsigned char type);
	virtual void RelayClick(ClickArgs args);
	virtual void RelayScroll(ScrollArgs args);
	virtual void RelayCursorDrag(DragArgs args);
	virtual void RelayKey(KeyArgs args);
	virtual void RelayText(TextArgs args);
};
};
};

#endif
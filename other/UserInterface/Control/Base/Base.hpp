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

/* what do Controls do ?

handle Events and/or Relay to children
change Size relative to Parent
change Visibility
change Layer (Depth)
change Color

*/

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
	bool	_Enabled;
	public:
	bool	IsEnabled() const;
	void	MakeEnabled();
	void	MakeDisabled();

	protected:
	bool	_Visible;
	public:
	bool	IsVisible() const;
	void	Show();
	void	Hide();

	protected:
	bool	_Opaque;
	public:
	bool	IsTransparent() const;
	bool	IsOpaque() const;
	void	MakeTransparent();
	void	MakeOpaque();

	public:
	bool	Drawable() const; // rename to Displayed
	bool	Interactible() const;

	public:
	bool			Deletable;		//should be deleted when Parent is deleted

	protected:
	// Anchor needs to change if these change ?
	Point2D			AnchorSize;
	Point2D			AnchorNormal;
	AxisBox2D		AnchorDist;

	AxisBox2D		AnchorMargin;
	AxisBox2D		AnchorBoarder; // hardcoced as 2 in Shader
	AxisBox2D		AnchorPadding;

	public:
	Anchor2D		Anchor;

	protected:
	AxisBox2D		DisplayBox;
	AxisBox2D		ContainerBox;
	// another Box for Text ?

	protected:
	bool			AnchorBoxChanged;

	public:
	ColorF4			ColorDefault;
	//Color			ColorDisabled; // Gray Text
	ColorF4			ColorHover;
	bool			ColorChanged;

	public:
	virtual ~Base();
	Base();

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
#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

#include "Data.hpp"

#include "UI/DisplayScale.hpp"
#include "UI/AxisBox.hpp"
#include "UI/Anchor.hpp"

#include "UserParameter/Mouse/Click.hpp"
#include "UserParameter/Mouse/Scroll.hpp"

#include "UserParameter/KeyBoard/Key.hpp"
#include "UserParameter/KeyBoard/Text.hpp"

#include "DataInclude.hpp"

#include "Miscellaneous/Container/Dynamic.hpp"
#include "Miscellaneous/EntryContainer/Dynamic.hpp"



namespace UI
{

namespace Control
{

class Manager;

class Base
{
	protected:
	Manager & ControlManager;
	
	protected:
	EntryContainer::Entry<Control::Inst_Data> Entry;
	private:
	Base * Parent;
	Container::Dynamic<Control::Base *> Children;

	public:
	float			Layer;

	public:
	Anchor2D		Anchor;

	protected:
	Point2D			AnchorSize;
	AxisBox2D		AnchorDist;
	Point2D			AnchorNormal;
	public:
	AxisBox2D		AnchorPadding;

	protected:
	AxisBox2D		AnchorBox;
	bool			AnchorBoxChanged;

	public:
	bool			Enabled;		//visible but cannot be interacted with by User, can be changed via code, Grayed out ?
	bool			Visible;		//is current and children visible
	bool			Opaque;			//is current invisible, does not effect children
	protected:
	bool			Drawable;		//should this currently be drawn ?

	public:
	Color			ColorDefault;
	//Color			ColorDisabled;
	Color			ColorHover;
	bool			ColorChanged;

	public:
	Base(Manager & manager);
	virtual ~Base();

	void ChildInsert(Base * control);

	//	for automatic Updating. should not be called by User
	public:
	void UpdateEntrys();

	public:

	//	Enabled
	void MakeEnabled();
	void MakeDisabled();

	//	Visibility
	void Show();
	void Hide();

	//	Transparent
	void MakeTransParent();
	void MakeOpaque();

	//	for automatic Updating. should not be called by User
	private:
	void UpdateVisibility();
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
	virtual void RelayClick(UserParameter::Mouse::Click params);
	virtual void RelayScroll(UserParameter::Mouse::Scroll params);
	virtual void RelayKey(UserParameter::KeyBoard::Key params);
	virtual void RelayText(UserParameter::KeyBoard::Text params);
};

};

};

#endif

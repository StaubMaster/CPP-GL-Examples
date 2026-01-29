#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

#include "Data.hpp"

#include "UI/Anchor.hpp"

#include "UserParameter/MouseDeclare.hpp"

#include "UserParameter/KeyBoard/Key.hpp"
#include "UserParameter/KeyBoard/Text.hpp"

#include "DataInclude.hpp"

#include "Miscellaneous/Container/Binary.hpp"
#include "Miscellaneous/EntryContainer/Binary.hpp"

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
	EntryContainer::Entry<Control::Inst_Data> ControlEntry;

	protected:
	Base * Parent;
	Container::Binary<Control::Base *> Children;

	public:
	float			Layer;

	protected:
	bool			_Enabled;		//visible but cannot be interacted with by User, can be changed via code, Grayed out ?
	bool			_Visible;		//is current and children visible
	bool			_Opaque;		//is current invisible, does not effect children

	//	these are based on the others
	//	have a function that "calculates" the value every time
	bool			_Drawable;		//should this currently be drawn ?
	bool			_Interactible;	//can be interacted with

	public:
	bool			Deletable;		//should be deleted when Parent is deleted

	public:
	Anchor2D		Anchor;

	protected:
	Point2D			AnchorSize;
	AxisBox2D		AnchorDist;
	Point2D			AnchorNormal;
	public:
	AxisBox2D		AnchorPadding;

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

	public:
	//	Enabled
	//bool IsEnabled();
	void MakeEnabled();
	void MakeDisabled();
	
	public:
	//	Visibility
	//bool Visible();
	void Show();
	void Hide();
	
	public:
	//	Transparent
	//bool IsTransparent();
	//bool IsOpaque();
	void MakeTransparent();
	void MakeOpaque();

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
	virtual void RelayClick(UserParameter::Mouse::Click params);
	virtual void RelayScroll(UserParameter::Mouse::Scroll params);
	virtual void RelayCursorDrag(UserParameter::Mouse::Drag params);
	virtual void RelayKey(UserParameter::KeyBoard::Key params);
	virtual void RelayText(UserParameter::KeyBoard::Text params);
};
};
};

#endif
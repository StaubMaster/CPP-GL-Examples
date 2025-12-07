#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

#include "Data.hpp"

#include "UI/DisplayScale.hpp"
#include "UI/AxisBox.hpp"
#include "UI/Anchor.hpp"
#include "UI/Parameter/Click.hpp"
#include "UI/Parameter/Key.hpp"
#include "UI/Parameter/Text.hpp"

#include "DataInclude.hpp"

#include "Miscellaneous/Container/Dynamic.hpp"
#include "Miscellaneous/EntryContainer/Dynamic.hpp"



#define CLICK_NONE    0b00
#define CLICK_PRESS   0b01
#define CLICK_HOLD    0b11
#define CLICK_RELEASE 0b10

#define CLICK_BUTTON_L 0
#define CLICK_BUTTON_R 1

namespace UI
{

namespace Control
{

struct Manager;

class Base
{
	protected:
	Manager & ControlManager;
	
	protected:
	EntryContainer::Entry<Control::Inst_Data> Entry;
	private:
	//Base * Parent;
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
	bool			Visible;
	//bool	Transparent	? makes removes Entry like Visible, but allows children to be visible
	//bool	Enabled		//visible but cannot be interacted with by User, can be changed via code

	Color			ColorDefault;
	Color			ColorHover;
	bool			ColorChanged;

	//	optional Relay functions
	public:
	void (*ClickFunc)(UI::Parameter::Click params);

	public:
	Base(Manager & manager);
	virtual ~Base();

	void ChildInsert(Base * control);

	public:
	void Info(std::string padding) const;

	//	for automatic Updating. should not be called by User
	public:
	void UpdateEntrys();
	protected:
	virtual void UpdateEntryAnchorBoxRelay();
	virtual void UpdateEntryColorRelay();
	virtual void UpdateEntrysRelay();

	//	can be called by User
	public:
	void Show();
	void Hide();

	//	for automatic Updating. should not be called by User
	private:
	void UpdateVisibility(bool make_visible);
	protected:
	virtual void UpdateVisibilityRelay(bool make_visible);

	//	for automatic Updating. should not be called by User
	public:
	void UpdateBox(const AxisBox2D & BaseBox);
	protected:
	virtual void UpdateBoxRelay();

	//	for automatic Updating. should not be called by User
	public:
	Base * CheckHover(Point2D mouse);

	//	for automatic Updating. should not be called by User
	public:
	void HoverEnter();
	void HoverLeave();
	virtual void RelayHover(unsigned char type);

	//	relay funciton to inherited Controls. should not be called by user
	//	put all Relay stuff into struct ?
	//	dont want in to clutter up stuff
	//	but if i put them in struct, then they would have to change things in the base
	//	which would require a referance, which is unnecassary
	public:
	virtual void RelayClick(UI::Parameter::Click params);
	virtual void RelayKey(UI::Parameter::Key params);
	virtual void RelayText(UI::Parameter::Text params);
};

};

};

#endif

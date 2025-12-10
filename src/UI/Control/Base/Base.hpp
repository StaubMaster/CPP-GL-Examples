#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

#include "Data.hpp"

#include "UI/DisplayScale.hpp"
#include "UI/AxisBox.hpp"
#include "UI/Anchor.hpp"

#include "UserParameter/Click.hpp"
#include "UserParameter/Scroll.hpp"
#include "UserParameter/Key.hpp"
#include "UserParameter/Text.hpp"

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
	/*
		rename Drawable
		Enabled and Visible have 2 Variants
		1. what this Control want to be
		2. what does Parent(recursive) allow
		have functions to check for combinations
		WantsEntry() { Drawable & Visible & Opaque }
		AcceptsUserInput() { WantsEntry() & Enabled }
	*/
	
	public:
	Color			ColorDefault;
	//Color			ColorDisabled;
	Color			ColorHover;
	bool			ColorChanged;

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
	void MakeEnabled();
	void MakeDisabled();

	void Show();
	void Hide();

	void MakeTransParent();
	void MakeOpaque();

	//	for automatic Updating. should not be called by User
	private:
	void UpdateVisibility();
	void InsertDrawingEntry();
	void RemoveDrawingEntry();
	virtual void InsertDrawingEntryRelay();
	virtual void RemoveDrawingEntryRelay();

	//	for automatic Updating. should not be called by User
	public:
	void UpdateBox();
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
	virtual void RelayClick(UserParameter::Click params);
	virtual void RelayScroll(UserParameter::Scroll params);
	virtual void RelayKey(UserParameter::Key params);
	virtual void RelayText(UserParameter::Text params);
};

};

};

#endif

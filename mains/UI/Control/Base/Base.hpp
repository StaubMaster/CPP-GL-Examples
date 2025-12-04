#ifndef  UI_CONTROL_BASE_HPP
# define UI_CONTROL_BASE_HPP

#include "Data.hpp"

#include "UI/DisplayScale.hpp"
#include "UI/AxisBox.hpp"
#include "UI/Anchor.hpp"

#include "DataInclude.hpp"

#include "Miscellaneous/Container/Dynamic.hpp"
#include "Miscellaneous/EntryContainer/Dynamic.hpp"



/*
most things need text now ?
and images ?
*/

/*	Manager
Text and Images also need a Manager ?
should they have their own Manager, or put everything into a UI Manager ?
probably make seperate Managers for now, and then make a general UI Manager for Controls Text and Images
*/

/*	Setting Anchors
only set the information needed for that Anchor
*/

/*	Click
should Click be in the Base or where its needed

Window:	might need Click. could be used for getting click on screen/clicking in general
Form:	not sure why I might need this here
Button:	needs Click, thats the whole point. it should actually allways need a Click. take in in Constructor ?
Text:	also allways needs a Click to get into Text

should Click Select/Focus the Control ? yes
important for Text, not really needed for anything else ?

allow Controls to be Disables/Inactive ?
so clicking them dosent do anything
*/

/*	what should Clicking do ?
check if Conrol is Enabled/Active
make Control Selected/put into Focus
call ClickFunction (if it exists)
*/

/*	Color/Texture/Display-State
Enabled, not Selected, not Hovering
Enabled, not Selected, Hovering
Enabled, Selected, not Hovering
Enabled, Selected, Hovering
Disabled

Toggle needs State Colors
maybe instead of Toggle, make it loop between different states ?
maybe left click goes foreward and right goes backward
*/

/*	Cursor
change Cursor when hovering Controls
*/

/*	other Controls
radio buttons (only one can be checked, unchecks others. use for Tabs ?)
Slider
*/

/*	how are Child Controls different from Base ?
Constructor sets Default stuff

Text: allows Text input/output
*/

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
	public:
		Manager & ControlManager;

		EntryContainer::Entry<Control::Inst_Data> Entry;
		Container::Dynamic<Control::Base *> Children;

		float			Layer;
		bool			Visible;

		Anchor2D		Anchor;

		Point2D			PixelMinDist;
		Point2D			PixelSize;
		Point2D			PixelMaxDist;

		AxisBox2D		PixelBox;
		Point2D			NormalCenter;

		Color			ColorDefault;
		Color			ColorHover;

		void (*ClickFunc)(unsigned char, unsigned char);

		//	Text
		//	Image ?

	public:
		Base(Manager & manager);
		virtual ~Base();

		//	get/set X/Y Min/Max
		//	would be useful for placing multiple things next to eachother

	public:
		void Info(std::string padding) const;

	public:
		void Show();
		void Hide();
	private:
		void ShowEntry();
		void HideEntry();
	public:
		void UpdateEntryAll();

	public:
		void UpdateBox(const AxisBox2D & BaseBox);
		bool UpdateHover(Point2D mouse);
};

};

};

#endif

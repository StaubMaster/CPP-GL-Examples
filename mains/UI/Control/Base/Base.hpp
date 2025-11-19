#ifndef  CONTROL_HPP
# define CONTROL_HPP

#include "Data.hpp"

#include "UI/DisplayScale.hpp"
#include "UI/AxisBox.hpp"
#include "UI/Anchor.hpp"

#include "DataInclude.hpp"

#include "Miscellaneous/ContainerDynamic.hpp"
#include "Miscellaneous/EntryContainer/EntryContainerDynamic.hpp"



/*	Setting Anchors
	only set the information needed for that Anchor
*/

/*	Click
how to handle
1 Function ?
how to handle both buttons
or Press vs Release vs Hold
just give that stuff to the function ?
or have a systen where the function gets "registered"
with certain conditions
and then only call the function when the conditions are met

I think giving stuff to the function is probably the easiest
*/

#define CLICK_NONE    0b00
#define CLICK_PRESS   0b01
#define CLICK_HOLD    0b11
#define CLICK_RELEASE 0b10

#define CLICK_BUTTON_L 0
#define CLICK_BUTTON_R 1



/*	Colors
some things dont need Hovering
and only need DefaultColor

also need a "Pressed" Color for some
like Buttons

just have Default in Base
and anything else is in whereever its needed

right now there is nothing in the nonBases
*/



namespace Control
{

struct Manager;

class Base
{
	public:
		Manager & ControlManager;

		EntryContainerDynamic<Control::Inst_Data>::Entry * Entry;
		ContainerDynamic<Control::Base *> Children;

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
		void Show();
		void Hide();
	private:
		void ShowEntry();
		void HideEntry();
		void UpdateEntryAll();

	public:
		void UpdateBox(const AxisBox2D & BaseBox);
		bool UpdateHover(Point2D mouse);
};
};

#endif

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
	public:
		struct Internal
		{
			bool	BoxChanged;
			bool	ColorChanged;

			void UpdateBox();
			void UpdateMouse();
			void Click();
			void Key();
		};
		struct External
		{
			void (*HoverEnter)();	//	Mouse is now over Control, wasn't last Frame
			void (*HoverLeave)();	//	Mouse is now not over Control, was last Frame
			void (*HoverMove)();	//	Mouse has new Position over Control
			void (*HoverOver)();	//	Mouse is over Control, called every Frame
			//	Hover(type)

			void (*Click)(unsigned char);
			//	ClickDown()
			//	ClickUp()
			//	ClickPress()
			//	ClickRelease()

			void (*SelectionBegin)();
			void (*SelectionEnd)();
			//	Selection(type)

			External();
		};

	public:
		Manager & ControlManager;

		EntryContainer::Entry<Control::Inst_Data> Entry;
		Container::Dynamic<Control::Base *> Children;

		float			Layer;
		bool			Visible;

		bool			ChangedBox;
		bool			ChangedColor;

		Anchor2D		Anchor;

		Point2D			PixelMinDist;
		Point2D			PixelSize;
		Point2D			PixelMaxDist;

		AxisBox2D		PixelBox;
		Point2D			NormalCenter;

		Color			ColorDefault;
		Color			ColorHover;

		void (*ClickFunc)(UI::Parameter::Click params);

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
		void UpdateEntrys();
	protected:
		virtual void UpdateEntrysRelay();

	public:
		void Show();
		void Hide();
	private:
		void UpdateVisibility(bool make_visible);
	protected:
		virtual void UpdateVisibilityRelay(bool make_visible);

	public:
		void UpdateBox(const AxisBox2D & BaseBox);
	protected:
		virtual void UpdateBoxRelay();

	public:
		Base * CheckHover(Point2D mouse);

	public:
		virtual void RelayClick(UI::Parameter::Click params);
		virtual void RelayKey(UI::Parameter::Key params);
		virtual void RelayText(UI::Parameter::Text params);
};

};

};

#endif

#ifndef  CONTROL_HPP
# define CONTROL_HPP

#include "Data.hpp"
#include "Manager.hpp"

#include "UI/DisplayScale.hpp"
#include "UI/AxisBox.hpp"
#include "UI/Anchor.hpp"

#include "DataInclude.hpp"

#include "Miscellaneous/ContainerDynamic.hpp"
#include "Miscellaneous/EntryContainer/EntryContainerDynamic.hpp"



/*	Setting Anchors
	only set the information needed for that Anchor
*/

/*
	Click() calls Click Function (if it exists)
		have seperate "Click" Functions
		for Press Release Hold
		and Left Right
		have variants for Hover / Selected

	should Hovering/Selected be remembered by Controls
	or the Control Manager
		Manager might be better
	Focus ? basically what I call Selected
*/

namespace Control
{

struct Manager;

class Base
{
	public:
		/*	should be able to "dynamically" allocate and free the Entry as needed
			needs to know the EntryContainer
			Control Manager ?
				also holds the Buffer and Shader

			Visible
			Show()
				sets Visible to false
				removes Entry
				removes Entrys of Children (recursive)
			Hide()
				sets Visible to true
				allocates Entry
				allocates Entrys of all Visible Children (recusrsivly)
		*/
		Manager & ControlManager;

		EntryContainerDynamic<Control::Inst_Data>::Entry * Entry;
		ContainerDynamic<Control::Base *> Children;

		float			Layer;
		bool			Visible;

		Anchor2D	Anchor;

		Point2D			PixelMinDist;
		Point2D			PixelSize;
		Point2D			PixelMaxDist;

		AxisBox2D		PixelBox;
		Point2D			NormalCenter;

		Color			ColorDefault;
		Color			ColorHover;

		bool			IsHover;
		bool			IsChildHover;

		//	Text
		//	Image ?

	public:
		Base(Manager & manager);
		virtual ~Base();

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

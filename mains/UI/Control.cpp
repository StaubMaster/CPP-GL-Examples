#ifndef  CONTROL_HPP
# define CONTROL_HPP

#include "DataInclude.hpp"
#include "AxisBox.cpp"
#include "Anchor.cpp"

#include "Miscellaneous/ContainerDynamic.hpp"
#include "Miscellaneous/EntryContainer/EntryContainerDynamic.hpp"



struct UI_Main_Data
{
	Point2D	Pos;

	UI_Main_Data() { }
	UI_Main_Data(Point2D pos) :
		Pos(pos)
	{ }
};
struct UI_Inst_Data
{
	Point2D	Min;
	Point2D	Max;
	float	Layer;
	Color Col;

	UI_Inst_Data() { }
	UI_Inst_Data(Point2D min, Point2D max, float layer, Color col) :
		Min(min),
		Max(max),
		Layer(layer),
		Col(col)
	{ }
};

class Control
{
	public:
		EntryContainerDynamic<UI_Inst_Data>::Entry * Entry;
		ContainerDynamic<Control *> Children;

		float			Layer;

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

	public:
		Control(EntryContainerDynamic<UI_Inst_Data>::Entry * entry) :
			Entry(entry)
		{ }
		~Control()
		{
			for (unsigned int i = 0; i < Children.Count(); i++)
			{
				delete Children[i];
			}
		}

	public:
		void UpdateBox(const AxisBox2D & BaseBox)
		{
			PixelBox = Anchor.Calculate(AxisBox2D(PixelMinDist, PixelMaxDist), PixelSize, NormalCenter, BaseBox);
			for (unsigned int i = 0; i < Children.Count(); i++)
			{
				Children[i] -> UpdateBox(PixelBox);
			}
		}

	public:
		void UpdateEntryBox(Point2D Size)
		{
			if (Entry != NULL)
			{
				(*Entry)[0].Min = Normal0ToNormal1(PixelToNormal0(PixelBox.Min, Size));
				(*Entry)[0].Max = Normal0ToNormal1(PixelToNormal0(PixelBox.Max, Size));
			}
			for (unsigned int i = 0; i < Children.Count(); i++)
			{
				Children[i] -> UpdateEntryBox(Size);
			}
		}
		void UpdateEntryDefault()
		{
			if (Entry != NULL)
			{
				(*Entry)[0].Layer = Layer;
				(*Entry)[0].Col = ColorDefault;
			}
			for (unsigned int i = 0; i < Children.Count(); i++)
			{
				Children[i] -> UpdateEntryDefault();
			}
		}
		bool UpdateHover(Point2D mouse)
		{
			if (PixelBox.Intersekt(mouse))
			{
				IsHover = true;
				unsigned int hover_idx = 0xFFFFFFFF;
				for (unsigned int i = 0; i < Children.Count(); i++)
				{
					if (Children[i] -> UpdateHover(mouse))
					{
						hover_idx = i;
					}
				}

				if (hover_idx != 0xFFFFFFFF)
				{
					IsChildHover = true;
					if (Entry != NULL)
					{
						(*Entry)[0].Col = ColorDefault;
					}
				}
				else
				{
					IsChildHover = false;
					if (Entry != NULL)
					{
						(*Entry)[0].Col = ColorHover;
					}
				}
				return true;
			}
			IsHover = false;
			if (IsChildHover)
			{
				for (unsigned int i = 0; i < Children.Count(); i++)
				{
					Children[i] -> UpdateHover(mouse);
				}
			}
			IsChildHover = false;

			if (Entry != NULL)
			{
				(*Entry)[0].Col = ColorDefault;
			}
			return false;
		}
};

#endif

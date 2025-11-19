#ifndef  CONTROL_MANAGER_HPP
# define CONTROL_MANAGER_HPP

#include "Data.hpp"
#include "Buffer.hpp"

#include "DataInclude.hpp"

#include "Miscellaneous/ContainerDynamic.hpp"
#include "Miscellaneous/EntryContainer/EntryContainerDynamic.hpp"

namespace Control
{
struct Manager
{
	Point2D ViewPortSize;

	ContainerDynamic<Control::Main_Data> Main_Data_Container;
	EntryContainerDynamic<Control::Inst_Data> Inst_Data_Container;

	BufferArray * BufferArray;

	void BufferInit()
	{
		BufferArray = new Control::BufferArray();

		Main_Data_Container.Insert(Control::Main_Data(Point2D(-1, -1)));
		Main_Data_Container.Insert(Control::Main_Data(Point2D(-1, +1)));
		Main_Data_Container.Insert(Control::Main_Data(Point2D(+1, -1)));
		Main_Data_Container.Insert(Control::Main_Data(Point2D(+1, -1)));
		Main_Data_Container.Insert(Control::Main_Data(Point2D(-1, +1)));
		Main_Data_Container.Insert(Control::Main_Data(Point2D(+1, +1)));
	}
	void BufferFree()
	{
		delete BufferArray;
	}

	void BufferUpdate()
	{
		BufferArray -> Use();
		BufferArray -> Main.BindData(GL_ARRAY_BUFFER, 0, sizeof(Control::Main_Data) * Main_Data_Container.Count(), Main_Data_Container.ToPointer(), GL_STREAM_DRAW);
		BufferArray -> Inst.BindData(GL_ARRAY_BUFFER, 0, sizeof(Control::Inst_Data) * Inst_Data_Container.Length, Inst_Data_Container.Data, GL_STREAM_DRAW);
		BufferArray -> Main.Count = Main_Data_Container.Count();
		BufferArray -> Inst.Count = Inst_Data_Container.Length;
	}
	void BufferDraw()
	{
		BufferArray -> Use();
		BufferArray -> Draw();
	}
};
};

#endif
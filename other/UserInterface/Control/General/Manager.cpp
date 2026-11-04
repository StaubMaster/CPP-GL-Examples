#include "Manager.hpp"

#include "Graphics/Shader/Code.hpp"
#include "DirectoryInfo.hpp"

#include "ValueType/_Include.hpp"





UI::Control::Manager * UI::Control::Manager::CurrentPointer = nullptr;
UI::Control::Manager & UI::Control::Manager::Current() { return *CurrentPointer; } // throw Exception instead of latting this cause a segfault ?
bool UI::Control::Manager::CheckCurrent() { return (UI::Control::Manager::CurrentPointer != nullptr); }
void UI::Control::Manager::ClearCurrent() { UI::Control::Manager::CurrentPointer = nullptr; }
bool UI::Control::Manager::IsCurrent() const { return (UI::Control::Manager::CurrentPointer == this); }
void UI::Control::Manager::MakeCurrent() { UI::Control::Manager::CurrentPointer = this; }





UI::Control::Manager::~Manager()
{
	/*for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		delete ObjectDatas[i];
	}*/
}
UI::Control::Manager::Manager()
	: Shader()
	, ShaderLayout()
	, Buffer()
	, BufferLayoutMain()
	, BufferLayoutInst()
//	, ObjectDatas()
	, Instances()
	, GraphicsExist(false)
	, GraphicsNeedMain(false)
{
	Shader.AssignLayout(ShaderLayout);

	Buffer.MainBuffer.AssignLayout(BufferLayoutMain);
	Buffer.InstBuffer.AssignLayout(BufferLayoutInst);
}



void UI::Control::Manager::InstancePut(const Control::Inst::Data & data)
{
	Instances.Insert(data);
}



void UI::Control::Manager::ChangeMedia(const DirectoryInfo & dir)
{
	Shader.Change({
		dir.File("Shaders/UI/Control.vert"),
		dir.File("Shaders/UI/Control.frag"),
	});
	BufferLayoutMain.Pos.Change(0);
	BufferLayoutInst.Box.Min.Change(1);
	BufferLayoutInst.Box.Max.Change(2);
	BufferLayoutInst.Layer.Change(3);
	BufferLayoutInst.Color.Change(4);
	BufferLayoutInst.Bound.Min.Change(5);
	BufferLayoutInst.Bound.Max.Change(6);
}

void UI::Control::Manager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Buffer.Create();
	Shader.Create();

	GraphicsExist = true;

	GraphicsNeedMain = true;
}
void UI::Control::Manager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Buffer.Delete();
	Shader.Delete();

	GraphicsExist = false;
}

void UI::Control::Manager::GraphicsInit()
{
	Buffer.Init();
}

void UI::Control::Manager::GraphicsPutMain()
{
	if (!(GraphicsNeedMain && GraphicsExist)) { return; }

	Container::Binary<Control::Main::Data> data;

	data.Insert(UI::Control::Main::Data(VectorF2(-1, -1)));
	data.Insert(UI::Control::Main::Data(VectorF2(+1, -1)));
	data.Insert(UI::Control::Main::Data(VectorF2(-1, +1)));
	data.Insert(UI::Control::Main::Data(VectorF2(-1, +1)));
	data.Insert(UI::Control::Main::Data(VectorF2(+1, -1)));
	data.Insert(UI::Control::Main::Data(VectorF2(+1, +1)));

	Buffer.MainBuffer.DataFull(data.ToVoid());
	Buffer.MainBuffer.Count = data.Count();

	GraphicsNeedMain = false;
}
void UI::Control::Manager::GraphicsPutInst()
{
	Buffer.InstBuffer.DataFull(Instances.ToVoid());
	Buffer.InstBuffer.Count = Instances.Count();
}

void UI::Control::Manager::GraphicsClear()
{
	Instances.Clear();
}
void UI::Control::Manager::GraphicsMake()
{
	/*for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		if (ObjectDatas[i] != nullptr)
		{
			ObjectData & obj = *ObjectDatas[i];
			InstancePut(obj);
			if (obj.Remove)
			{
				ObjectDatas.RemoveAt(i);
				delete &obj;
				i--;
			}
		}
	}*/
}

#include <iostream>
void UI::Control::Manager::GraphicsDraw()
{
	std::cout << "UI::Control::Manager::GraphicsDraw():" << __LINE__ << '\n';
	GraphicsPutMain();
	std::cout << "UI::Control::Manager::GraphicsDraw():" << __LINE__ << '\n';
	GraphicsPutInst();
	std::cout << "UI::Control::Manager::GraphicsDraw():" << __LINE__ << '\n';

	Shader.Bind();
	std::cout << "UI::Control::Manager::GraphicsDraw():" << __LINE__ << '\n';

	Buffer.Bind();
	std::cout << "UI::Control::Manager::GraphicsDraw():" << __LINE__ << '\n';
	Buffer.Draw();
	std::cout << "UI::Control::Manager::GraphicsDraw():" << __LINE__ << '\n';
}

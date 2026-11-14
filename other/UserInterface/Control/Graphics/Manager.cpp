#include "Manager.hpp"

#include "Graphics/Shader/Code.hpp"
#include "DirectoryInfo.hpp"

#include "ValueType/_Include.hpp"





UI::ControlGraphics::Manager * UI::ControlGraphics::Manager::CurrentPointer = nullptr;
UI::ControlGraphics::Manager & UI::ControlGraphics::Manager::Current() { return *CurrentPointer; } // throw Exception instead of latting this cause a segfault ?
bool UI::ControlGraphics::Manager::CheckCurrent() { return (UI::ControlGraphics::Manager::CurrentPointer != nullptr); }
void UI::ControlGraphics::Manager::ClearCurrent() { UI::ControlGraphics::Manager::CurrentPointer = nullptr; }
bool UI::ControlGraphics::Manager::IsCurrent() const { return (UI::ControlGraphics::Manager::CurrentPointer == this); }
void UI::ControlGraphics::Manager::MakeCurrent() { UI::ControlGraphics::Manager::CurrentPointer = this; }





UI::ControlGraphics::Manager::~Manager()
{
	/*for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		delete ObjectDatas[i];
	}*/
}
UI::ControlGraphics::Manager::Manager()
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



void UI::ControlGraphics::Manager::InstancesClear()
{
	Instances.Clear();
}
/*void UI::ControlGraphics::Manager::InstancesMake()
{
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
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
	}
}*/
void UI::ControlGraphics::Manager::InstancePut(const Inst::Data & data)
{
	Instances.Insert(data);
}



void UI::ControlGraphics::Manager::ChangeMedia(const DirectoryInfo & dir)
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

void UI::ControlGraphics::Manager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Buffer.Create();
	Shader.Create();

	GraphicsExist = true;

	GraphicsNeedMain = true;
}
void UI::ControlGraphics::Manager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Buffer.Delete();
	Shader.Delete();

	GraphicsExist = false;
}

void UI::ControlGraphics::Manager::GraphicsInit()
{
	Buffer.Init();
}

void UI::ControlGraphics::Manager::GraphicsPutMain()
{
	if (!(GraphicsNeedMain && GraphicsExist)) { return; }

	Container::Binary<Main::Data> data;

	data.Insert(Main::Data(VectorF2(-1, -1)));
	data.Insert(Main::Data(VectorF2(+1, -1)));
	data.Insert(Main::Data(VectorF2(-1, +1)));
	data.Insert(Main::Data(VectorF2(-1, +1)));
	data.Insert(Main::Data(VectorF2(+1, -1)));
	data.Insert(Main::Data(VectorF2(+1, +1)));

	Buffer.MainBuffer.DataFull(data.ToVoid());
	Buffer.MainBuffer.Count = data.Count();

	GraphicsNeedMain = false;
}
void UI::ControlGraphics::Manager::GraphicsPutInst()
{
	Buffer.InstBuffer.DataFull(Instances.ToVoid());
	Buffer.InstBuffer.Count = Instances.Count();
}

void UI::ControlGraphics::Manager::GraphicsDraw()
{
	GraphicsPutMain();
	GraphicsPutInst();

	Shader.Bind();
	Buffer.Bind();
	Buffer.Draw();
}

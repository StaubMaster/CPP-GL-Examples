#include "Manager.hpp"
#include "ObjectData.hpp"

#include "Graphics/Shader/Code.hpp"
#include "DirectoryInfo.hpp"

#include "ValueType/_Include.hpp"





UI::Control::Manager * UI::Control::Manager::CurrentPointer = nullptr;
UI::Control::Manager & UI::Control::Manager::Current() { return *CurrentPointer; }
bool UI::Control::Manager::CheckCurrent() { return (UI::Control::Manager::CurrentPointer != nullptr); }
void UI::Control::Manager::ClearCurrent() { UI::Control::Manager::CurrentPointer = nullptr; }
bool UI::Control::Manager::IsCurrent() const { return (UI::Control::Manager::CurrentPointer == this); }
void UI::Control::Manager::MakeCurrent() { UI::Control::Manager::CurrentPointer = this; }





UI::Control::Manager::~Manager()
{
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		delete ObjectDatas[i];
	}
}
UI::Control::Manager::Manager()
	: Shader()
	, ShaderLayout()
	, Buffer()
	, BufferLayoutMain()
	, BufferLayoutInst()
	, ObjectDatas()
	, Instances()
	, GraphicsExist(false)
	, GraphicsNeedMain(false)
{
	Shader.UniformLayout = &ShaderLayout;
	ShaderLayout.Shader = &Shader;

	Buffer.MainBuffer.Layout = &BufferLayoutMain;
	Buffer.InstBuffer.Layout = &BufferLayoutInst;
}



UI::Control::ObjectData * UI::Control::Manager::PlaceObject()
{
	ObjectData * obj = new ObjectData();
	ObjectDatas.Insert(obj);
	return obj;
}
UI::Control::ObjectData * UI::Control::Manager::CopyObject(const ObjectData * obj)
{
	if (obj == nullptr) { return nullptr; }
	ObjectData * ret = PlaceObject();
	*ret = *obj;
	return ret;
}



void UI::Control::Manager::ChangeMedia(const DirectoryInfo & dir)
{
	{
		Shader.Change({
			dir.File("Shaders/UI/Control.vert"),
			dir.File("Shaders/UI/Control.frag"),
		});
	}
	{
		BufferLayoutMain.Pos.Change(0);
		BufferLayoutInst.Box.Min.Change(1);
		BufferLayoutInst.Box.Max.Change(2);
		BufferLayoutInst.Layer.Change(3);
		BufferLayoutInst.Col.Change(4);
	}
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

void UI::Control::Manager::GraphicsMain()
{
	if (!(GraphicsNeedMain && GraphicsExist)) { return; }

	Container::Binary<Control::Main::BufferData> data;

	data.Insert(UI::Control::Main::BufferData(VectorF2(-1, -1)));
	data.Insert(UI::Control::Main::BufferData(VectorF2(-1, +1)));
	data.Insert(UI::Control::Main::BufferData(VectorF2(+1, -1)));
	data.Insert(UI::Control::Main::BufferData(VectorF2(+1, -1)));
	data.Insert(UI::Control::Main::BufferData(VectorF2(-1, +1)));
	data.Insert(UI::Control::Main::BufferData(VectorF2(+1, +1)));

	Buffer.MainBuffer.DataFull(data.ToVoid());
	Buffer.MainBuffer.Count = data.Count();

	GraphicsNeedMain = false;
}
void UI::Control::Manager::GraphicsInst()
{
	MakeInstances();
	Buffer.InstBuffer.DataFull(Instances.ToVoid());
	Buffer.InstBuffer.Count = Instances.Count();
}

void UI::Control::Manager::PlaceInstance(const ObjectData & obj)
{
	Inst::BufferData data;
	data.Box = obj.Box;
	data.Layer = obj.Layer;
	data.Col = obj.Color;
	Instances.Insert(data);
}
void UI::Control::Manager::MakeInstances()
{
	Instances.Clear();
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		if (ObjectDatas[i] != nullptr)
		{
			ObjectData & obj = *ObjectDatas[i];
			if (obj.Display)
			{
				PlaceInstance(obj);
			}
			if (obj.Remove)
			{
				ObjectDatas.RemoveAt(i);
				delete &obj;
				i--;
			}
		}
	}
}



void UI::Control::Manager::Draw()
{
	GraphicsMain();
	GraphicsInst();

	Shader.Bind();

	//Buffer.Bind();
	//Buffer.MainBuffer.Update();
	//Buffer.InstBuffer.Update();

	//Buffer.InitAttributeLayoutMain(Buffer.MainBuffer);
	//Buffer.InitAttributeLayoutInst(Buffer.InstBuffer);

	//Buffer.ChangeAttributeLayoutMain(BufferLayoutMain);
	//Buffer.ChangeAttributeLayoutInst(BufferLayoutInst);

//	Buffer.MainBuffer.Bind();
//	BufferLayoutMain.Bind();
//
//	Buffer.InstBuffer.Bind();
//	BufferLayoutInst.Bind();

	Buffer.Bind();
	Buffer.Draw();
}

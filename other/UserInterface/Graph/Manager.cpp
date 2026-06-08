#include "Manager.hpp"
#include "ObjectData.hpp"

#include "Graphics/Shader/Code.hpp"
#include "DirectoryInfo.hpp"

#include "ValueType/_Include.hpp"

#include "ValueType/_Show.hpp"
#include <iostream>





UI::Graph::Manager * UI::Graph::Manager::CurrentPointer = nullptr;
UI::Graph::Manager & UI::Graph::Manager::Current() { return *CurrentPointer; }
bool UI::Graph::Manager::CheckCurrent() { return (UI::Graph::Manager::CurrentPointer != nullptr); }
void UI::Graph::Manager::ClearCurrent() { UI::Graph::Manager::CurrentPointer = nullptr; }
bool UI::Graph::Manager::IsCurrent() const { return (UI::Graph::Manager::CurrentPointer == this); }
void UI::Graph::Manager::MakeCurrent() { UI::Graph::Manager::CurrentPointer = this; }





UI::Graph::Manager::~Manager()
{
	std::cout << "  ----  " << "UI::Graph::Manager::~Manager()" << "\n";
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		delete ObjectDatas[i];
	}
}
UI::Graph::Manager::Manager()
	: Shader()
	, ShaderLayout()
	, Buffer()
	, GraphicsExist(false)
{
	std::cout << "  ++++  " << "UI::Graph::Manager::Manager()" << "\n";

	Shader.UniformLayout = &ShaderLayout;
	ShaderLayout.Shader = &Shader;

	Buffer.MainBuffer.AttributeLayout = &BufferLayout;
}



UI::Graph::ObjectData * UI::Graph::Manager::PlaceObject()
{
	ObjectData * obj = new ObjectData();
	ObjectDatas.Insert(obj);
	return obj;
}
UI::Graph::ObjectData * UI::Graph::Manager::CopyObject(const ObjectData * obj)
{
	if (obj == nullptr) { return nullptr; }
	ObjectData * ret = PlaceObject();
	*ret = *obj;
	return ret;
}



void UI::Graph::Manager::ChangeMedia(const DirectoryInfo & dir)
{
	{
		Shader.Change({
			dir.File("Shaders/UI/Graph.vert"),
			dir.File("Shaders/UI/Graph.frag"),
		});
	}
	{
		BufferLayout.Box.Min.Change(0);
		BufferLayout.Box.Max.Change(1);
		BufferLayout.Pos.Change(2);
		BufferLayout.Col.Change(3);
	}
}

void UI::Graph::Manager::GraphicsCreate()
{
	if (GraphicsExist) { return; }

	Buffer.Create();
	Shader.Create();

	GraphicsExist = true;
}
void UI::Graph::Manager::GraphicsDelete()
{
	if (!GraphicsExist) { return; }

	Buffer.Delete();
	Shader.Delete();

	GraphicsExist = false;
}

#include "ValueType/_Show.hpp"
#include <iostream>
void UI::Graph::Manager::PlaceInstance(const ObjectData & obj)
{
	BufferData data;
	data.Box = obj.Box;
	data.Col = obj.Col;

	float limit = obj.Values -> Limit - 1;

	if (obj.Values -> Count != 0)
	{
		unsigned int i = obj.Values -> Index;
		if (i != 0) { i--; }
		else { i = obj.Values -> Count - 1; }

		for (unsigned int j = 1; j < obj.Values -> Count; j++)
		{
			unsigned int i0 = i;
			unsigned int i1 = i0;
			if (i1 != 0) { i1--; }
			else { i1 = obj.Values -> Count - 1; }

			float val0 = obj.Values -> Data[i0];
			float val1 = obj.Values -> Data[i1];

			val0 = (val0 - obj.Center) / obj.Magnitede;
			val1 = (val1 - obj.Center) / obj.Magnitede;

			data.Pos = VectorF2((((j - 1) / limit) * 2) - 1, val0); Instances.Insert(data);
			data.Pos = VectorF2((((j - 0) / limit) * 2) - 1, val1); Instances.Insert(data);

			i = i1;
		}

		data.Col = ColorF4(0, 0, 0);
		data.Pos = VectorF2(-1, 0); Instances.Insert(data);
		data.Pos = VectorF2(+1, 0); Instances.Insert(data);
		data.Pos = VectorF2(-1, -1); Instances.Insert(data);
		data.Pos = VectorF2(+1, -1); Instances.Insert(data);
		data.Pos = VectorF2(-1, +1); Instances.Insert(data);
		data.Pos = VectorF2(+1, +1); Instances.Insert(data);

		/*{
			float val;

			val = ((obj.Values -> Min()) - Center) / Magnitede;
			data.Pos = VectorF2(-1, val); Instances.Insert(data);
			data.Pos = VectorF2(+1, val); Instances.Insert(data);
			
			val = ((obj.Values -> Max()) - Center) / Magnitede;
			data.Pos = VectorF2(-1, val); Instances.Insert(data);
			data.Pos = VectorF2(+1, val); Instances.Insert(data);
			
			val = ((obj.Values -> Average()) - Center) / Magnitede;
			data.Pos = VectorF2(-1, val); Instances.Insert(data);
			data.Pos = VectorF2(+1, val); Instances.Insert(data);
		}*/
	}
}
void UI::Graph::Manager::MakeInstances()
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



void UI::Graph::Manager::Draw()
{
	Buffer.MainBuffer.DataFull(Instances.ToVoid());

	Shader.Bind();

	Buffer.Bind();
	Buffer.MainBuffer.Update();
	Buffer.Draw();
}

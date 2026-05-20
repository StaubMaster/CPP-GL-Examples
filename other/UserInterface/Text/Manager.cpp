#include "Manager.hpp"
#include "ObjectData.hpp"

#include "ValueType/_Include.hpp"

#include "Miscellaneous/Container/Array.hpp"
#include "Graphics/Shader/Code.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"

#include "ValueType/_Show.hpp"
#include <iostream>





UI::Text::Manager * UI::Text::Manager::CurrentPointer = nullptr;
UI::Text::Manager & UI::Text::Manager::Current() { return *CurrentPointer; }
bool UI::Text::Manager::CheckCurrent() { return (UI::Text::Manager::CurrentPointer != nullptr); }
void UI::Text::Manager::ClearCurrent() { UI::Text::Manager::CurrentPointer = nullptr; }
bool UI::Text::Manager::IsCurrent() const { return (UI::Text::Manager::CurrentPointer == this); }
void UI::Text::Manager::MakeCurrent() { UI::Text::Manager::CurrentPointer = this; }





UI::Text::Manager::~Manager()
{
	std::cout << "  ----  " << "UI::Text::Manager::~Manager()" << '\n';
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		delete ObjectDatas[i];
	}
	delete TextFont;
}
UI::Text::Manager::Manager()
	: Shader()
	, Buffer()
	, ObjectDatas()
	, InstancesBlock()
	, InstancesArray()
	, TextFont(nullptr)
	, Pallet_Texture()
	, GraphicsExist(false)
	, TextureAssigned(false)
	, BufferMainAttributesBound(false)
	, BufferInstAttributesBound(false)
	, BufferMainNewData(false)
	, BufferInstNewData(false)
{
	std::cout << "  ++++  " << "UI::Text::Manager::Manager()" << '\n';
}

void UI::Text::Manager::InitMedia(DirectoryInfo & media_dir)
{
	{
		Container::Array<::Shader::Code> code({
			::Shader::Code(media_dir.File("Shaders/UI/Text.vert")),
			::Shader::Code(media_dir.File("Shaders/UI/Text.frag")),
		});
		Shader.Change(code);
	}
	{
		Buffer.Main.Pos.Change(0);
		Buffer.Inst.Pos.Change(1);
		Buffer.Inst.Pallet.Min.Change(2);
		Buffer.Inst.Pallet.Max.Change(3);
		Buffer.Inst.Bound.Min.Change(4);
		Buffer.Inst.Bound.Max.Change(5);
		Buffer.Inst.Color.Change(6);
	}
}



UI::Text::ObjectData * UI::Text::Manager::MakeObject()
{
	ObjectData * obj = new ObjectData();
	ObjectDatas.Insert(obj);
	return obj;
}
UI::Text::ObjectData * UI::Text::Manager::CopyObject(const ObjectData * obj)
{
	if (obj == nullptr) { return nullptr; }
	return MakeObject();
}



static unsigned int LineCount(const char * text)
{
	unsigned int count = 0;
	for (unsigned int i = 0; text[i] != '\0'; i++)
	{
		if (text[i] == '\n')
		{
			count++;
		}
	}
	return count;
}
static unsigned int LineLength(const char * text, unsigned int i)
{
	unsigned int len = 0;
	while (text[i] != '\0')
	{
		if (text[i] == '\n')
		{
			break;
		}
		len++;
		i++;
	}
	return len;
}

#include "../../Examples/NoisePlane/Telemetry/StopWatch.hpp"
#include "../../Examples/NoisePlane/Telemetry/ValueAverager.hpp"
#include <iomanip>

//static StopWatch				WatchTotal;
//static StopWatch				WatchClear;
//static StopWatch				WatchDisplay;
//static StopWatch				WatchRemove;
//static StopWatch				WatchAlign;
//static StopWatch				WatchLoop;
//static StopWatch				WatchOther;
//static StopWatch				WatchFind;
//static StopWatch				WatchAssign;
//static StopWatch				WatchInsert;
//static StopWatch				WatchNext0;
//static StopWatch				WatchNext1;
//static StopWatch				WatchArray;

//static ValueAverager<float>		TimeTotal(64);
//static ValueAverager<float>		TimeClear(64);
//static ValueAverager<float>		TimeDisplay(64);
//static ValueAverager<float>		TimeRemove(64);
//static ValueAverager<float>		TimeAlign(64);
//static ValueAverager<float>		TimeLoop(64);
//static ValueAverager<float>		TimeOther(64);
//static ValueAverager<float>		TimeFind(64);
//static ValueAverager<float>		TimeAssign(64);
//static ValueAverager<float>		TimeInsert(64);
//static ValueAverager<float>		TimeNext0(64);
//static ValueAverager<float>		TimeNext1(64);
//static ValueAverager<float>		TimeArray(64);

/*static void TimeClearFunc()
{
	WatchTotal.Clear();
	WatchClear.Clear();
	WatchDisplay.Clear();
	WatchRemove.Clear();
	WatchAlign.Clear();
	WatchLoop.Clear();
	WatchOther.Clear();
	WatchFind.Clear();
	WatchAssign.Clear();
	WatchInsert.Clear();
	WatchNext0.Clear();
	WatchNext1.Clear();
	WatchArray.Clear();
}*/
/*static void TimeValueFunc()
{
	TimeTotal.NewValue(WatchTotal.ElapsedTime());
	TimeClear.NewValue(WatchClear.ElapsedTime());
	TimeDisplay.NewValue(WatchDisplay.ElapsedTime());
	TimeRemove.NewValue(WatchRemove.ElapsedTime());
	TimeAlign.NewValue(WatchAlign.ElapsedTime());
	TimeLoop.NewValue(WatchLoop.ElapsedTime());
	TimeOther.NewValue(WatchOther.ElapsedTime());
	TimeFind.NewValue(WatchFind.ElapsedTime());
	TimeAssign.NewValue(WatchAssign.ElapsedTime());
	TimeInsert.NewValue(WatchInsert.ElapsedTime());
	TimeNext0.NewValue(WatchNext0.ElapsedTime());
	TimeNext1.NewValue(WatchNext1.ElapsedTime());
	TimeArray.NewValue(WatchArray.ElapsedTime());
}*/

void UI::Text::Manager::ShowInstancesTime()
{
	//std::cout << "Total   " << std::fixed << TimeTotal.Average() << '\n';
	//std::cout << "Clear   " << std::fixed << TimeClear.Average() << '\n';
	//std::cout << "Display " << std::fixed << TimeDisplay.Average() << '\n';
	//std::cout << "Remove  " << std::fixed << TimeRemove.Average() << '\n';
	//std::cout << "Align   " << std::fixed << TimeAlign.Average() << '\n';
	//std::cout << "Loop    " << std::fixed << TimeLoop.Average() << '\n';
	//std::cout << "Other   " << std::fixed << TimeOther.Average() << '\n';
	//std::cout << "Find    " << std::fixed << TimeFind.Average() << '\n';
	//std::cout << "Assign  " << std::fixed << TimeAssign.Average() << '\n';
	//std::cout << "Insert  " << std::fixed << TimeInsert.Average() << '\n';
	//std::cout << "Next0   " << std::fixed << TimeNext0.Average() << '\n';
	//std::cout << "Next1   " << std::fixed << TimeNext1.Average() << '\n';
	//std::cout << "Array   " << std::fixed << TimeArray.Average() << '\n';
	//std::cout << '\n';
}

void UI::Text::Manager::MakeObjectInstances(const ObjectData & obj)
{
	//WatchAlign.Start();

	unsigned int line_count = LineCount(obj.Text.c_str());
	unsigned int line_idx = 0;
	unsigned int line_len = LineLength(obj.Text.c_str(), 0);

	VectorF2 rel_chr;
	switch (obj.CharacterAlignmentX)
	{
		case Alignment::Min: rel_chr.X = +0.5f; break;
		case Alignment::Mid: rel_chr.X =  0.0f; break;
		case Alignment::Max: rel_chr.X = -0.5f; break;
	}
	switch (obj.CharacterAlignmentY)
	{
		case Alignment::Min: rel_chr.Y = +0.5f; break;
		case Alignment::Mid: rel_chr.Y =  0.0f; break;
		case Alignment::Max: rel_chr.Y = -0.5f; break;
	}

	VectorF2 text_alignment;
	switch (obj.TextAlignmentX)
	{
		case Alignment::Min: text_alignment.X = 0.0f; break;
		case Alignment::Mid: text_alignment.X = 0.5f; break;
		case Alignment::Max: text_alignment.X = 1.0f; break;
	}
	switch (obj.TextAlignmentY)
	{
		case Alignment::Min: text_alignment.Y = 0.0f; break;
		case Alignment::Mid: text_alignment.Y = 0.5f; break;
		case Alignment::Max: text_alignment.Y = 1.0f; break;
	}

	VectorF2 rel_txt;
	rel_txt.Y = -(line_count * text_alignment.Y);

	//WatchAlign.Stop();

	//WatchLoop.Start();

	for (unsigned int i = 0; i < obj.Text.length(); i++)
	{
		char c = obj.Text[i];
		if (c == ' ')
		{
			line_idx++;
			continue;;
		}
		if (c == '\n')
		{
			rel_txt.Y++;
			line_idx = 0;
			line_len = LineLength(obj.Text.c_str(), i + 1);
			continue;
		}

		//WatchNext0.Start();
		UI::Text::Inst_Data & data = InstancesBlock.MakeNext();
		//WatchNext0.Stop();

		//WatchOther.Start();
		rel_txt.X = (line_idx + text_alignment.X) - (line_len * text_alignment.X);
		line_idx++;
		data.Pos = obj.TextPosition + (obj.CharacterSize * (rel_txt + rel_chr));
		//WatchOther.Stop();

		//WatchFind.Start();
		data.Pallet = (*TextFont)[c].Box;
		//WatchFind.Stop();

		//VectorF2 size = (obj.CharacterSize * 0.5f);
		//if (obj.Bound.InnerBox(BoxF2(data.Pos - size, data.Pos + size)).IsNormal()) // this is slow

		//WatchAssign.Start();
		data.Bound = obj.Bound;
		data.Color = obj.Color;
		//WatchAssign.Stop();

		//WatchInsert.Start();
		//InstancesBlock.Insert(data);
		//WatchInsert.Stop();

		//WatchNext1.Start();
		InstancesBlock.Next();
		//WatchNext1.Stop();
	}

	//WatchLoop.Stop();
}
void UI::Text::Manager::MakeInstances()
{
	//TimeClearFunc();

	//WatchTotal.Start();

	//WatchClear.Start();
	InstancesBlock.Clear();
	InstancesArray.Clear();
	//WatchClear.Stop();

	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		if (ObjectDatas[i] != nullptr)
		{
			ObjectData & obj = *ObjectDatas[i];
			if (obj.Display)
			{
				//WatchDisplay.Start();
				MakeObjectInstances(obj);
				//WatchDisplay.Stop();
			}
			if (obj.Remove)
			{
				//WatchRemove.Start();
				ObjectDatas.RemoveAt(i);
				delete &obj;
				i--;
				//WatchRemove.Stop();
			}
		}
	}
	BufferInstNewData = true;

	//WatchArray.Start();
	InstancesArray = InstancesBlock.ToArray();
	//WatchArray.Stop();

	//WatchTotal.Stop();

	//TimeValueFunc();
}





void UI::Text::Manager::GraphicsCreate()
{
	if (!GraphicsExist)
	{
		Shader.Create();
		Buffer.Create();
		Pallet_Texture.Create();
		GraphicsExist = true;
		TextureAssigned = false;
		BufferMainAttributesBound = false;
		BufferInstAttributesBound = false;
		BufferMainNewData = true;
	}
}
void UI::Text::Manager::GraphicsDelete()
{
	if (GraphicsExist)
	{
		Buffer.Delete();
		Shader.Delete();
		Pallet_Texture.Delete();
		GraphicsExist = false;
	}
}

void UI::Text::Manager::TextureAssign()
{
	if (!GraphicsExist || TextureAssigned) { return; }

	Pallet_Texture.Bind();
	Pallet_Texture.Assign(TextFont -> AtlasTexture);
	Pallet_Texture.FilterMin(Texture::Base::FilterMinType::Linear);

	TextureAssigned = true;
}
void UI::Text::Manager::BufferMainAttributesBind()
{
	if (!GraphicsExist || BufferMainAttributesBound) { return; }

	Buffer.Main.Update();

	BufferMainAttributesBound = true;
}
void UI::Text::Manager::BufferInstAttributesBind()
{
	if (!GraphicsExist || BufferInstAttributesBound) { return; }

	Buffer.Inst.Update();

	BufferInstAttributesBound = true;
}

void UI::Text::Manager::BufferMainUpdateData()
{
	if (!GraphicsExist || !BufferMainNewData) { return; }

	Container::Binary<UI::Text::Main_Data> data;

	data.Insert(UI::Text::Main_Data(VectorF2(-1, -1)));
	data.Insert(UI::Text::Main_Data(VectorF2(-1, +1)));
	data.Insert(UI::Text::Main_Data(VectorF2(+1, -1)));
	data.Insert(UI::Text::Main_Data(VectorF2(+1, -1)));
	data.Insert(UI::Text::Main_Data(VectorF2(-1, +1)));
	data.Insert(UI::Text::Main_Data(VectorF2(+1, +1)));

	Buffer.Main.DataFull(data.ToVoid());

	BufferMainNewData = false;
}
void UI::Text::Manager::BufferInstUpdateData()
{
	if (!GraphicsExist || !BufferInstNewData) { return; }

	Buffer.Inst.DataFull(InstancesArray.ToVoid());

	BufferInstNewData = false;
}



void UI::Text::Manager::Draw()
{
	if (!GraphicsExist) { return; }

	TextureAssign();

	BufferMainAttributesBind();
	BufferMainUpdateData();

	BufferInstAttributesBind();
	BufferInstUpdateData();

	Shader.Bind();
	Pallet_Texture.Bind();
	Buffer.Bind();

	Buffer.Draw();
}

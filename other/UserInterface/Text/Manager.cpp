#include "Manager.hpp"
#include "ObjectData.hpp"

#include "ValueType/_Include.hpp"

#include "Generics/Container/Array.hpp"
#include "Graphics/Shader/Code.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"

#include <iostream>
#include "ValueType/_Show.hpp"





UI::Text::Manager * UI::Text::Manager::CurrentPointer = nullptr;
UI::Text::Manager & UI::Text::Manager::Current() { return *CurrentPointer; }
bool UI::Text::Manager::CheckCurrent() { return (UI::Text::Manager::CurrentPointer != nullptr); }
void UI::Text::Manager::ClearCurrent() { UI::Text::Manager::CurrentPointer = nullptr; }
bool UI::Text::Manager::IsCurrent() const { return (UI::Text::Manager::CurrentPointer == this); }
void UI::Text::Manager::MakeCurrent() { UI::Text::Manager::CurrentPointer = this; }





UI::Text::Manager::~Manager()
{
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		delete ObjectDatas[i];
	}
	delete Font;
}
UI::Text::Manager::Manager()
	: Shader()
	, ShaderLayout()
	, Buffer()
	, LayoutMain()
	, LayoutInst()
	, ObjectDatas()
	, InstancesBlock()
	, InstancesArray()
	, Font(nullptr)
	, FontTexture()
	, FontPalletsList()
	, FontBuffer(GL::BufferDataUsage::StreamDraw)
	, TextsList()
	, TextsBuffer(GL::BufferDataUsage::StreamDraw)
	, GraphicsExist(false)
	, TextureAssigned(false)
{
	Shader.UniformLayout = &ShaderLayout;
	ShaderLayout.Shader = &Shader;

	Buffer.MainLayout = &LayoutMain; Buffer.MainBuffer.SizeOf = sizeof(Main_Data);
	Buffer.InstLayout = &LayoutInst; Buffer.InstBuffer.SizeOf = sizeof(Inst_Data);
}

void UI::Text::Manager::ChangeMedia(const DirectoryInfo & media_dir)
{
	{
		Shader.Change({
			media_dir.File("Shaders/UI/Text.vert"),
			media_dir.File("Shaders/UI/Text.frag"),
		});
	}
	{
		LayoutMain.Pos.Change(0);
		LayoutInst.TextPos.Change(1);
		LayoutInst.CharIdx.Change(2);
		LayoutInst.TextIdx.Change(3);
	}
}
#include "Font/Font.hpp"
void UI::Text::Manager::InitFont()
{
	unsigned int idx = 0;

	for (unsigned int j = 0; j < Font -> CharacterRanges.Count(); j++)
	{
		for (unsigned int i = 0; i < Font -> CharacterRanges[j] -> Characters.Count(); i++)
		{
			FontPalletsList.Insert(Font -> CharacterRanges[j] -> Characters[i].Box);
			idx++;
		}
	}

	for (unsigned int i = 0; i < Font -> Characters.Count(); i++)
	{
		FontPalletsList.Insert(Font -> Characters[i].Box);
		idx++;
	}

	FontPalletsList.Insert(Font -> DefaultCharacter.Box);
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

#include "../../Examples/General/Telemetry/StopWatch.hpp"
#include "../../Examples/General/Telemetry/ValueAccumulator.hpp"
#include "../../Examples/General/UnitToString.hpp"

//#define TELEMETRY_TIME

#ifdef TELEMETRY_TIME
static StopWatch				WatchTotal;
static StopWatch				WatchClear;
static StopWatch				WatchDisplay;
static StopWatch				WatchRemove;
static StopWatch				WatchAlign;
static StopWatch				WatchLoop;
static StopWatch				WatchOther;
static StopWatch				WatchFind;
static StopWatch				WatchAssign;
static StopWatch				WatchInsert;
static StopWatch				WatchNext0;
static StopWatch				WatchNext1;
static StopWatch				WatchArray;
#endif

#ifdef TELEMETRY_TIME
static ValueAccumulator<float>		TimeTotal(64);
static ValueAccumulator<float>		TimeClear(64);
static ValueAccumulator<float>		TimeDisplay(64);
static ValueAccumulator<float>		TimeRemove(64);
static ValueAccumulator<float>		TimeAlign(64);
static ValueAccumulator<float>		TimeLoop(64);
static ValueAccumulator<float>		TimeOther(64);
static ValueAccumulator<float>		TimeFind(64);
static ValueAccumulator<float>		TimeAssign(64);
static ValueAccumulator<float>		TimeInsert(64);
static ValueAccumulator<float>		TimeNext0(64);
static ValueAccumulator<float>		TimeNext1(64);
static ValueAccumulator<float>		TimeArray(64);
#endif

#ifdef TELEMETRY_TIME
static void TimeClearFunc()
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
}
#endif
#ifdef TELEMETRY_TIME
static void TimeValueFunc()
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
}
#endif

void UI::Text::Manager::ShowInstancesTime()
{
#ifdef TELEMETRY_TIME
	std::cout << "Total   " << ToString(TimeTotal.Average()) << '\n';
	std::cout << "Clear   " << ToString(TimeClear.Average()) << '\n';
	std::cout << "Display " << ToString(TimeDisplay.Average()) << '\n';
	std::cout << "Remove  " << ToString(TimeRemove.Average()) << '\n';
	std::cout << "Align   " << ToString(TimeAlign.Average()) << '\n';
	std::cout << "Loop    " << ToString(TimeLoop.Average()) << '\n';
	std::cout << "Other   " << ToString(TimeOther.Average()) << '\n';
	std::cout << "Find    " << ToString(TimeFind.Average()) << '\n';
	std::cout << "Assign  " << ToString(TimeAssign.Average()) << '\n';
	std::cout << "Insert  " << ToString(TimeInsert.Average()) << '\n';
	std::cout << "Next0   " << ToString(TimeNext0.Average()) << '\n';
	std::cout << "Next1   " << ToString(TimeNext1.Average()) << '\n';
	std::cout << "Array   " << ToString(TimeArray.Average()) << '\n';
	std::cout << '\n';
#endif
}

void UI::Text::Manager::MakeObjectInstances(const ObjectData & obj)
{
#ifdef TELEMETRY_TIME
	WatchAlign.Start();
#endif

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

#ifdef TELEMETRY_TIME
	WatchAlign.Stop();
#endif

#ifdef TELEMETRY_TIME
	WatchLoop.Start();
#endif

	VectorF2 cursor;
	bool cursor_found = false;

	for (unsigned int i = 0; i < obj.Text.length(); i++)
	{
		char c = obj.Text[i];
		if (c == ' ')
		{
			if (obj.DisplayTextCursor && i == obj.TextCursorIndex)
			{
				rel_txt.X = (line_idx + text_alignment.X) - (line_len * text_alignment.X);
				cursor = obj.TextPosition + (obj.CharacterSize * (rel_txt + rel_chr));
				cursor_found = true;
			}
			line_idx++;
			continue;
		}
		if (c == '\n')
		{
			if (obj.DisplayTextCursor && i == obj.TextCursorIndex)
			{
				rel_txt.X = (line_idx + text_alignment.X) - (line_len * text_alignment.X);
				cursor = obj.TextPosition + (obj.CharacterSize * (rel_txt + rel_chr));
				cursor_found = true;
			}
			rel_txt.Y++;
			line_idx = 0;
			line_len = LineLength(obj.Text.c_str(), i + 1);
			continue;
		}

#ifdef TELEMETRY_TIME
		WatchNext0.Start();
#endif
		UI::Text::Inst_Data & data = InstancesBlock.MakeNext();
#ifdef TELEMETRY_TIME
		WatchNext0.Stop();
#endif

#ifdef TELEMETRY_TIME
		WatchOther.Start();
#endif
		rel_txt.X = (line_idx + text_alignment.X) - (line_len * text_alignment.X);
		data.TextPos = obj.TextPosition + (obj.CharacterSize * (rel_txt + rel_chr));

#ifdef TELEMETRY_TIME
		WatchOther.Stop();
#endif

#ifdef TELEMETRY_TIME
		WatchFind.Start();
#endif
		data.CharIdx = Font -> FindCodeIndex(c);
#ifdef TELEMETRY_TIME
		WatchFind.Stop();
#endif

		//VectorF2 size = (obj.CharacterSize * 0.5f);
		//if (obj.Bound.InnerBox(BoxF2(data.Pos - size, data.Pos + size)).IsNormal()) // this is slow

#ifdef TELEMETRY_TIME
		WatchAssign.Start();
#endif
		data.TextIdx = TextsList.Count();
#ifdef TELEMETRY_TIME
		WatchAssign.Stop();
#endif

#ifdef TELEMETRY_TIME
		WatchInsert.Start();
#endif
		//InstancesBlock.Insert(data);
#ifdef TELEMETRY_TIME
		WatchInsert.Stop();
#endif

#ifdef TELEMETRY_TIME
		WatchNext1.Start();
#endif
		InstancesBlock.Next();
#ifdef TELEMETRY_TIME
		WatchNext1.Stop();
#endif
		line_idx++;

		if (obj.DisplayTextCursor && i == obj.TextCursorIndex)
		{
			cursor = data.TextPos;
			cursor_found = true;
		}
	}

	if (obj.DisplayTextCursor)
	{
		if (!cursor_found)
		{
			rel_txt.X = (line_idx + text_alignment.X) - (line_len * text_alignment.X);
			cursor = obj.TextPosition + (obj.CharacterSize * (rel_txt + rel_chr));
		}

		UI::Text::Inst_Data & data = InstancesBlock.MakeNext();
		data.TextPos = cursor;
		data.CharIdx = Font -> FindCodeIndex('^');
		data.TextIdx = TextsList.Count();
		InstancesBlock.Next();
	}

	TextData data;
	data.Bound = obj.Bound;
	data.Color = obj.Color;
	data.CharSize = obj.CharacterSize;
	TextsList.Insert(data);

#ifdef TELEMETRY_TIME
	WatchLoop.Stop();
#endif
}
void UI::Text::Manager::MakeInstances()
{
#ifdef TELEMETRY_TIME
	TimeClearFunc();
	WatchTotal.Start();
#endif

#ifdef TELEMETRY_TIME
	WatchClear.Start();
#endif
	TextsList.Clear();
	InstancesBlock.Clear();
	InstancesArray.Clear();
#ifdef TELEMETRY_TIME
	WatchClear.Stop();
#endif

	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		if (ObjectDatas[i] != nullptr)
		{
			ObjectData & obj = *ObjectDatas[i];
			if (obj.Display)
			{
#ifdef TELEMETRY_TIME
				WatchDisplay.Start();
#endif
				MakeObjectInstances(obj);
#ifdef TELEMETRY_TIME
				WatchDisplay.Stop();
#endif
			}
			if (obj.Remove)
			{
#ifdef TELEMETRY_TIME
				WatchRemove.Start();
#endif
				ObjectDatas.RemoveAt(i);
				delete &obj;
				i--;
#ifdef TELEMETRY_TIME
				WatchRemove.Stop();
#endif
			}
		}
	}
	Buffer.InstDataHave = true;

#ifdef TELEMETRY_TIME
	WatchArray.Start();
#endif
	InstancesArray = InstancesBlock.ToArray();
#ifdef TELEMETRY_TIME
	WatchArray.Stop();
#endif

#ifdef TELEMETRY_TIME
	WatchTotal.Stop();
	TimeValueFunc();
#endif
}





void UI::Text::Manager::GraphicsCreate()
{
	if (!GraphicsExist)
	{
		Shader.Create();
		Buffer.Create();
		FontTexture.Create();
		FontBuffer.Create();
		TextsBuffer.Create();
		GraphicsExist = true;
		TextureAssigned = false;
		Buffer.MainDataWant = true;
		Buffer.MainDataHave = false;
		Buffer.InstDataWant = false;
		Buffer.InstDataHave = false;
	}
}
void UI::Text::Manager::GraphicsDelete()
{
	if (GraphicsExist)
	{
		Shader.Delete();
		Buffer.Delete();
		FontTexture.Delete();
		FontBuffer.Delete();
		TextsBuffer.Delete();
		GraphicsExist = false;
	}
}

void UI::Text::Manager::GraphicsInit()
{
	Buffer.Init();
}

void UI::Text::Manager::TextureAssign()
{
	if (!GraphicsExist || TextureAssigned) { return; }

	FontTexture.Bind();
	FontTexture.Assign(Font -> AtlasTexture);
	FontTexture.FilterMin(Texture::Base::FilterMinType::Linear);
	FontTexture.FilterMag(Texture::Base::FilterMagType::Linear);

	TextureAssigned = true;
}

// do this once in GraphicsInit ?
void UI::Text::Manager::BufferMainUpdateData()
{
	if (!GraphicsExist || !Buffer.MainDataWant) { return; }

	Container::Binary<UI::Text::Main_Data> data;

	data.Insert(UI::Text::Main_Data(VectorF2(-1, -1)));
	data.Insert(UI::Text::Main_Data(VectorF2(-1, +1)));
	data.Insert(UI::Text::Main_Data(VectorF2(+1, -1)));
	data.Insert(UI::Text::Main_Data(VectorF2(+1, -1)));
	data.Insert(UI::Text::Main_Data(VectorF2(-1, +1)));
	data.Insert(UI::Text::Main_Data(VectorF2(+1, +1)));

	Buffer.MainDataWant = false;
	Buffer.MainDataHave = true;

	Buffer.MainBuffer.DataFull(data.ToVoid());

	Buffer.MainDataHave = false;
}
void UI::Text::Manager::BufferInstUpdateData()
{
	if (!GraphicsExist || !Buffer.InstDataHave) { return; }

	Buffer.InstBuffer.DataFull(InstancesArray.ToVoid());

	Buffer.InstDataHave = false;
}



void UI::Text::Manager::Draw()
{
	if (!GraphicsExist) { return; }

	Shader.Bind();
	Buffer.Bind();
	//Buffer.InitAttributes();

	/*{
		FontTexture.Bind();
		int val;

		glGetTexParameteriv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, &val);
		if (val == (int)Texture::Base::FilterMagType::Linear ) { std::cout << "Mag: Linear \n"; }
		if (val == (int)Texture::Base::FilterMagType::Nearest) { std::cout << "Mag: Nearest\n"; }

		glGetTexParameteriv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, &val);
		if (val == (int)Texture::Base::FilterMinType::Linear ) { std::cout << "Min: Linear \n"; }
		if (val == (int)Texture::Base::FilterMinType::Nearest) { std::cout << "Min: Nearest\n"; }

		std::cout << '\n';
	}*/

	// do this stuff once / somewhere else
	// check for Limit, display error, dont throw
	{
		const unsigned int binding = 0;
		FontBuffer.Bind();
		FontBuffer.BindBase(binding);
		FontBufferData data;
		for (unsigned int i = 0; i < FontPalletsList.Count(); i++)
		{
			data.Array[i] = FontPalletsList[i];
		}
		FontBuffer.DataFull(Container::Void(data));
		ShaderLayout.Bind(ShaderLayout.Pallets, binding);
	}
	{
		const unsigned int binding = 1;
		TextsBuffer.BindBase(binding);
		TextsBufferData data;
		for (unsigned int i = 0; i < TextsList.Count(); i++)
		{
			data.Array[i] = TextsList[i];
		}
		TextsBuffer.DataFull(Container::Void(data));
		ShaderLayout.Bind(ShaderLayout.Texts, binding);
	}

	FontTexture.Bind();
	TextureAssign();

	BufferMainUpdateData();

	BufferInstUpdateData();

	FontBuffer.Bind();
	TextsBuffer.Bind();
	Buffer.Draw();
}

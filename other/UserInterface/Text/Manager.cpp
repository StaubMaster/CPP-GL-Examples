#include "Manager.hpp"
#include "ObjectData.hpp"

#include "ValueType/_Include.hpp"

#include "Generics/Container/Array.hpp"
#include "Graphics/Shader/Code.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"

#include <iostream>





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
	delete TextFont;
}
UI::Text::Manager::Manager()
	: Shader()
	, ShaderLayout()
	, Buffer()
	, ObjectDatas()
	, InstancesBlock()
	, InstancesArray()
	, FontPalletMin(128)
	, FontPalletMax(128)
	, TextBoundMin(32)
	, TextBoundMax(32)
	, TextColor(32)
	, TextFont(nullptr)
	, Pallet_Texture()
	, GraphicsExist(false)
	, TextureAssigned(false)
	, BufferMainAttributesBound(false)
	, BufferInstAttributesBound(false)
	, BufferMainNewData(false)
	, BufferInstNewData(false)
{
	Shader.UniformLayout = &ShaderLayout;
	ShaderLayout.Shader = &Shader;
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
		LayoutInst.Pos.Change(1);
		LayoutInst.PalletIdx.Change(2);
		LayoutInst.TextIdx.Change(3);
		Buffer.MainBuffer.Init(LayoutMain);
		Buffer.InstBuffer.Init(LayoutInst);
	}
}
#include "Font/Font.hpp"
void UI::Text::Manager::InitFont()
{
	unsigned int idx = 0;

	for (unsigned int j = 0; j < TextFont -> CharacterRanges.Count(); j++)
	{
		for (unsigned int i = 0; i < TextFont -> CharacterRanges[j] -> Characters.Count(); i++)
		{
			FontPalletMin[idx] = (TextFont -> CharacterRanges[j] -> Characters[i].Box.Min);
			FontPalletMax[idx] = (TextFont -> CharacterRanges[j] -> Characters[i].Box.Max);
			idx++;
		}
	}

	for (unsigned int i = 0; i < TextFont -> Characters.Count(); i++)
	{
		FontPalletMin[idx] = (TextFont -> Characters[i].Box.Min);
		FontPalletMax[idx] = (TextFont -> Characters[i].Box.Max);
		idx++;
	}

	FontPalletMin[idx] = (TextFont -> DefaultCharacter.Box.Min);
	FontPalletMax[idx] = (TextFont -> DefaultCharacter.Box.Max);

	Shader.Bind();
	ShaderLayout.PalletArrayMin.Put(FontPalletMin.Memory());
	ShaderLayout.PalletArrayMax.Put(FontPalletMax.Memory());
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
	if (TextArrayIdx == 64)
	{
		std::cerr << "!!!! Text Limit 64 reached !!!!\n";
		return;
	}

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

	TextBoundMin[TextArrayIdx] = obj.Bound.Min;
	TextBoundMax[TextArrayIdx] = obj.Bound.Max;
	TextColor[TextArrayIdx] = obj.Color;

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
		data.Pos = obj.TextPosition + (obj.CharacterSize * (rel_txt + rel_chr));

#ifdef TELEMETRY_TIME
		WatchOther.Stop();
#endif

#ifdef TELEMETRY_TIME
		WatchFind.Start();
#endif
		data.PalletIdx = (*TextFont).FindCodeIndex(c);
#ifdef TELEMETRY_TIME
		WatchFind.Stop();
#endif

		//VectorF2 size = (obj.CharacterSize * 0.5f);
		//if (obj.Bound.InnerBox(BoxF2(data.Pos - size, data.Pos + size)).IsNormal()) // this is slow

#ifdef TELEMETRY_TIME
		WatchAssign.Start();
#endif
		data.TextIdx = TextArrayIdx;
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
			cursor = data.Pos;
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
		data.Pos = cursor;
		data.PalletIdx = (*TextFont).FindCodeIndex('^');
		data.TextIdx = TextArrayIdx;
		InstancesBlock.Next();
	}

	TextArrayIdx++;

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
	TextArrayIdx = 0;
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
	BufferInstNewData = true;

	Shader.Bind();
	ShaderLayout.TextBoundArrayMin.Put(TextBoundMin.Memory());
	ShaderLayout.TextBoundArrayMax.Put(TextBoundMax.Memory());
	ShaderLayout.TextColorArray.Put(TextColor.Memory());

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

	Buffer.MainBuffer.Update();

	BufferMainAttributesBound = true;
}
void UI::Text::Manager::BufferInstAttributesBind()
{
	if (!GraphicsExist || BufferInstAttributesBound) { return; }

	Buffer.InstBuffer.Update();

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

	Buffer.MainBuffer.DataFull(data.ToVoid());

	BufferMainNewData = false;
}
void UI::Text::Manager::BufferInstUpdateData()
{
	if (!GraphicsExist || !BufferInstNewData) { return; }

	Buffer.InstBuffer.DataFull(InstancesArray.ToVoid());

	BufferInstNewData = false;
}



void UI::Text::Manager::Draw()
{
	if (!GraphicsExist) { return; }

	Shader.Bind();
	Pallet_Texture.Bind();

	TextureAssign();

	Buffer.Bind();

	BufferMainAttributesBind();
	BufferMainUpdateData();

	BufferInstAttributesBind();
	BufferInstUpdateData();

	Buffer.Draw();
}

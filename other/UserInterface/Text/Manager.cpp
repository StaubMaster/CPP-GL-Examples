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
	delete TextFont;
}
UI::Text::Manager::Manager()
	: Shader()
	, Buffer()
	, ObjectDatas()
	, Instances()
	, TextFont(nullptr)
	, Pallet_Texture()
	, GraphicsExist(false)
	, GraphicsNeedInit(false)
	, GraphicsNeedMain(false)
{
	std::cout << "  ++++  " << "UI::Text::Manager::Manager()" << '\n';
}



UI::Text::ObjectData * UI::Text::Manager::PlaceObject()
{
	ObjectData * obj = new ObjectData();
	ObjectDatas.Insert(obj);
	return obj;
}
UI::Text::ObjectData * UI::Text::Manager::CopyObject(const ObjectData * obj)
{
	if (obj == nullptr) { return nullptr; }
	return PlaceObject();
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



void UI::Text::Manager::GraphicsCreate()
{
	if (!GraphicsExist)
	{
		Shader.Create();
		Buffer.Create();
		Pallet_Texture.Create();
		GraphicsExist = true;
		GraphicsNeedInit = true;
		GraphicsNeedMain = true;
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



void UI::Text::Manager::GraphicsInit()
{
	if (!(GraphicsNeedInit && GraphicsExist)) { return; }

	Buffer.Main.Init();
	Buffer.Inst.Init();

	Pallet_Texture.Bind();
	Pallet_Texture.Assign(TextFont -> AtlasTexture);
	Pallet_Texture.FilterMin(Texture::Base::FilterMinType::Linear);

	GraphicsNeedInit = false;
}
void UI::Text::Manager::GraphicsMain()
{
	if (!(GraphicsNeedMain && GraphicsExist)) { return; }

	Container::Binary<UI::Text::Main_Data> data;

	data.Insert(UI::Text::Main_Data(Point2D(-1, -1)));
	data.Insert(UI::Text::Main_Data(Point2D(-1, +1)));
	data.Insert(UI::Text::Main_Data(Point2D(+1, -1)));
	data.Insert(UI::Text::Main_Data(Point2D(+1, -1)));
	data.Insert(UI::Text::Main_Data(Point2D(-1, +1)));
	data.Insert(UI::Text::Main_Data(Point2D(+1, +1)));

	Buffer.Main.Data(data);

	GraphicsNeedMain = false;
}
void UI::Text::Manager::GraphicsInst()
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
				ObjectDatas.Remove(i);
				delete &obj;
				i--;
			}
		}
	}
	Buffer.Inst.Data(Instances);
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

void UI::Text::Manager::PlaceInstance(const ObjectData & obj)
{
	unsigned int line_count = LineCount(obj.Text.c_str());
	unsigned int line_idx = 0;
	unsigned int line_len = LineLength(obj.Text.c_str(), 0);

	Point2D rel_chr;
	switch (obj.CharacterAlignmentX)
	{
		case Alignment::Min: rel_chr.X = -0.5f; break;
		case Alignment::Mid: rel_chr.X =  0.0f; break;
		case Alignment::Max: rel_chr.X = +0.5f; break;
	}
	switch (obj.CharacterAlignmentY)
	{
		case Alignment::Min: rel_chr.Y = -0.5f; break;
		case Alignment::Mid: rel_chr.Y =  0.0f; break;
		case Alignment::Max: rel_chr.Y = +0.5f; break;
	}

	Point2D rel_txt;
	switch (obj.TextAlignmentY)
	{
		case Alignment::Min: rel_txt.Y = -(line_count * 0.0f); break;
		case Alignment::Mid: rel_txt.Y = -(line_count * 0.5f); break;
		case Alignment::Max: rel_txt.Y = -(line_count * 1.0f); break;
	}

	UI::Text::Inst_Data data;
	for (unsigned int i = 0; i < obj.Text.length(); i++)
	{
		if (obj.Text[i] == ' ')
		{
			line_idx++;
			continue;;
		}
		if (obj.Text[i] == '\n')
		{
			rel_txt.Y += 1;
			line_idx = 0;
			line_len = LineLength(obj.Text.c_str(), i + 1);
			continue;
		}

		switch (obj.TextAlignmentX)
		{
			case Alignment::Min: rel_txt.X = (line_idx + 0.0f) - (line_len * 0.0f); break;
			case Alignment::Mid: rel_txt.X = (line_idx + 0.5f) - (line_len * 0.5f); break;
			case Alignment::Max: rel_txt.X = (line_idx + 1.0f) - (line_len * 1.0f); break;
		}

		line_idx++;

		// check if Character is in Bound ?
		data.Pos = obj.TextPosition + (obj.CharacterSize * (rel_txt + rel_chr));
		data.Pallet = TextFont -> CharacterBoxFromCode(obj.Text[i]); // this will need to be bofore check for non MonoSpace
		Point2D size = (obj.CharacterSize * 0.5f);

		// any Intersection ?
		// but has to touch somehow ?
		// InnerBox.Normal() ?
		if (obj.Bound.IntersectInclusive(BoxF2(data.Pos - size, data.Pos + size)).Any(true))
		{
			data.Bound = obj.Bound;
			data.Color = obj.Color;
			Instances.Insert(data);
		}
	}
}



void UI::Text::Manager::Draw()
{
	GraphicsInit();
	GraphicsMain();
	GraphicsInst();

	Shader.Bind();
	Pallet_Texture.Bind();
	Buffer.Bind();

	Buffer.Draw();
}

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
	, Instances()
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

void UI::Text::Manager::MakeObjectInstances(const ObjectData & obj)
{
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
			rel_txt.Y++;
			line_idx = 0;
			line_len = LineLength(obj.Text.c_str(), i + 1);
			continue;
		}

		rel_txt.X = (line_idx + text_alignment.X) - (line_len * text_alignment.X);

		line_idx++;

		// check if Character is in Bound ?
		data.Pos = obj.TextPosition + (obj.CharacterSize * (rel_txt + rel_chr));
		data.Pallet = TextFont -> CharacterBoxFromCode(obj.Text[i]); // this will need to be before check for non MonoSpace
		VectorF2 size = (obj.CharacterSize * 0.5f);

		//if (obj.Bound.InnerBox(BoxF2(data.Pos - size, data.Pos + size)).IsNormal()) // this is slow
		{
			data.Bound = obj.Bound;
			data.Color = obj.Color;
			Instances.Insert(data); // this is slow
			// use a BlockList ?
		}
	}
}
void UI::Text::Manager::MakeInstances()
{
	Instances.Clear();
	for (unsigned int i = 0; i < ObjectDatas.Count(); i++)
	{
		if (ObjectDatas[i] != nullptr)
		{
			ObjectData & obj = *ObjectDatas[i];
			if (obj.Display)
			{
				MakeObjectInstances(obj);
			}
			if (obj.Remove)
			{
				ObjectDatas.RemoveAt(i);
				delete &obj;
				i--;
			}
		}
	}
	BufferInstNewData = true;
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

	Buffer.Main.Init();

	BufferMainAttributesBound = true;
}
void UI::Text::Manager::BufferInstAttributesBind()
{
	if (!GraphicsExist || BufferInstAttributesBound) { return; }

	Buffer.Inst.Init();

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

	Buffer.Inst.DataFull(Instances.ToVoid());

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

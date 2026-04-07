#include "Manager.hpp"
#include "ObjectData.hpp"

#include "ValueType/_Include.hpp"

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

	Pallet_Texture.Delete();
	delete TextFont;
}
UI::Text::Manager::Manager()
	: Shader()
	, Buffer()
	, ObjectDatas()
	, Instances()
	, TextFont(nullptr)
	, Pallet_Texture()
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



void UI::Text::Manager::GraphicsCreate()
{
	Shader.Create();
	Buffer.Create();
}
void UI::Text::Manager::GraphicsDelete()
{
	Buffer.Delete();
	Shader.Delete();
}



void UI::Text::Manager::GraphicsInit()
{
	Buffer.Main.Init();
	Buffer.Inst.Init();
}
void UI::Text::Manager::GraphicsMain()
{
	Container::Binary<UI::Text::Main_Data> data;
	data.Insert(UI::Text::Main_Data(Point2D(-1, -1)));
	data.Insert(UI::Text::Main_Data(Point2D(-1, +1)));
	data.Insert(UI::Text::Main_Data(Point2D(+1, -1)));
	data.Insert(UI::Text::Main_Data(Point2D(+1, -1)));
	data.Insert(UI::Text::Main_Data(Point2D(-1, +1)));
	data.Insert(UI::Text::Main_Data(Point2D(+1, +1)));
	Buffer.Main.Change(data);
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
	Buffer.Inst.Change(Instances);
}

/* Text Alignment

								Pos.X
X Min								|########################
X Mid					############|############
X Max		########################|

Y Min		###################
			##########
Y Mid		###############
			###################
Y Max		###########
*/

/* Character Alignment

   Min Mid Max
Min	0---1---2
	|		|
	|		|
Mid	3	4	5
	|		|
	|		|
Max	6---7---8

move the Character / Text so that Pos is at Number n
*/

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
	Point2D CharacterSize = Point2D(20, 20);

	unsigned int line_count = LineCount(obj.Text.c_str());
	unsigned int line_idx = 0;
	unsigned int line_len = LineLength(obj.Text.c_str(), 0);

	Point2D rel;
	if (obj.AlignmentY == Alignment::Min)
	{
		rel.Y = 0;
	}
	if (obj.AlignmentY == Alignment::Mid)
	{
		rel.Y = -(line_count * 0.5f);
	}
	if (obj.AlignmentY == Alignment::Max)
	{
		rel.Y = -(line_count * 1.0f);
	}

	UI::Text::Inst_Data data;
	for (unsigned int i = 0; i < obj.Text.length(); i++)
	{
		if (obj.Text[i] == '\n')
		{
			rel.X = 0;
			rel.Y += 1;
			line_idx = 0;
			line_len = LineLength(obj.Text.c_str(), i + 1);
			continue;
		}

		if (obj.AlignmentX == Alignment::Min)
		{
			rel.X = (line_idx + 0.0f);
		}
		if (obj.AlignmentX == Alignment::Mid)
		{
			rel.X = (line_idx + 0.5f) - (line_len * 0.5f);
		}
		if (obj.AlignmentX == Alignment::Max)
		{
			rel.X = (line_idx + 1.0f) - (line_len * 1.0f);
		}

		line_idx++;

		data.Pos = obj.Pos + (CharacterSize * rel);
		data.Pallet = TextFont -> CharacterBoxFromCode(obj.Text[i]);
		data.Bound = obj.Bound;
		Instances.Insert(data);
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

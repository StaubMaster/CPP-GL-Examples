
#include <iostream>

#include "Debug.hpp"

#include "Window.hpp"
#include "Miscellaneous/Function/Object.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"

#include "ValueTypeShow.hpp"

#include "Miscellaneous/Container/Fixed.hpp"

#include "Graphics/Shader/Code.hpp"
#include "Graphics/Shader/Base.hpp"

#include "Graphics/Buffer/ArrayBase.hpp"
#include "Graphics/Buffer/Base.hpp"

#include "Graphics/Attribute/Point2D.hpp"
#include "Graphics/Attribute/ColorF4.hpp"

#include "Graphics/UniformsInclude.hpp"
#include "Graphics/MultiformsInclude.hpp"

#include "Graphics/Texture/Array2D.hpp"



//#include "UI/Anchor.hpp"
//
//#include "UI/Control/Base/Manager.hpp"
//#include "UI/ControlsInclude.hpp"

#include "Text/Manager.hpp"

#include <string>
#include <sstream>
#include <iostream>



struct MainContext
{
DirectoryInfo ShaderDir;
DirectoryInfo ImageDir;
DirectoryInfo TextDir;

Window window;

UI::Text::Manager UI_Text_Manager;
EntryContainer::Entry<UI::Text::Inst_Data> TextEntry;

MainContext()
	: ShaderDir("../../media/Shaders")
	, ImageDir("../../media/Images")
	, TextDir("../../media/Text")
	, window()
	, UI_Text_Manager()
{ }
~MainContext()
{ }



void Make()
{
	{
		Container::Fixed<::Shader::Code> code(2);
		code.Insert(::Shader::Code(ShaderDir.File("UI/Text.vert")));
		code.Insert(::Shader::Code(ShaderDir.File("UI/Text.frag")));
		UI_Text_Manager.Shader.Change(code);
	}
	UI_Text_Manager.Shader.Create();
	UI_Text_Manager.BufferArray.Create();

	{
		UI_Text_Manager.TextFont = UI::Text::Font::Parse(TextDir.File("Font0.atlas"));
		UI_Text_Manager.Pallet_Texture.Create();
		UI_Text_Manager.Pallet_Texture.Bind();
		UI_Text_Manager.Pallet_Texture.Assign(UI_Text_Manager.TextFont -> AtlasTexture);
		UI_Text_Manager.Pallet_Texture.FilterMin(Texture::Base::FilterMinType::Linear);
	}

	{
		TextEntry.Allocate(UI_Text_Manager.Inst_Data_Container, 16 * 8);
	}

	window.DefaultColor = ColorF4(1, 0, 0);

	UI_Text_Manager.BufferArray.Main.Init();
	UI_Text_Manager.BufferArray.Inst.Init();
}

void InitRun()
{
	GL::Disable(GL::Capability::DepthTest);
	GL::Disable(GL::Capability::CullFace);

	std::cout << "Init ...\n";

//	UI_Init();

//	Container::Fixed<Shader::Base *> shaders(2);
//	shaders.Insert(&(UI_Control_Manager -> Shader));
//	shaders.Insert(&(UI_Text_Manager -> Shader));

//	Multi_WindowSize = new Multiform::WindowBufferSize2D("WindowSize");
//	Multi_WindowSize -> FindUniforms(shaders);

//	UI_Make();

	std::cout << "Init done\n";

	Make();
}
void FreeRun()
{
	std::cout << "Free ...\n";

//	delete Multi_WindowSize;

//	UI_Free();

	std::cout << "Free done\n";
}

void ShowText(const char * text)
{
	std::string Text = text;
	//Point2D CharacterSize = Point2D(32, 32);
	Point2D CharacterSize = Point2D(20, 20);
	Point2D center = window.Size.Buffer.Half;

	for (unsigned int i = 0; i < TextEntry.Length(); i++)
	{
		//TextEntry[i].Pos = Point2D((min.X + (CharacterSize.X * 0.5f)) + (i * CharacterSize.X), center.Y);
		TextEntry[i].Pos = Point2D((center.X + (CharacterSize.X * 0.5f)) + (i * CharacterSize.X), center.Y);
		//if (UI_Text_Manager != NULL)
		{
			if (i < Text.length())
			{ TextEntry[i].Pallet = UI_Text_Manager.TextFont -> CharacterBoxFromCode(Text[i]); }
			else
			{ TextEntry[i].Pallet = UI_Text_Manager.TextFont -> CharacterBoxFromCode('\0'); }
		}
		//TextEntry[i].Bound = AnchorBox;
		TextEntry[i].Bound = AxisBox2D(Point2D(), window.Size.Buffer.Full);
	}
}
void ShowAllCharacters()
{
	//Point2D CharacterSize = Point2D(32, 32);
	Point2D CharacterSize = Point2D(20, 20);
	Point2D center = window.Size.Buffer.Half;

	unsigned int i = 0;
	for (unsigned int y = 0; y < 8; y++)
	{
		for (unsigned int x = 0; x < 16; x++)
		{
			TextEntry[i].Pos = Point2D(center.X - (CharacterSize.X * (x - 8.0f)), center.Y - (CharacterSize.Y * (y - 4.0f)));
			TextEntry[i].Pallet.Min = Point2D(x / 16.0f, y / 8.0f);
			TextEntry[i].Pallet.Max = TextEntry[i].Pallet.Min + Point2D(1 / 16.0f, 1 / 8.0f);
			TextEntry[i].Bound = AxisBox2D(Point2D(), window.Size.Buffer.Full);
			i++;
		}
	}
}

void Frame(double timeDelta)
{
	(void)timeDelta;

	ShowText("test Text");
	//ShowAllCharacters();

	UI_Text_Manager.Draw();

//	UI_Frame();
}

void Resize(const ::DisplaySize & DisplaySize)
{
	(void)DisplaySize;

	UI_Text_Manager.Shader.DisplaySize.Put(DisplaySize);
	
//	Multi_WindowSize -> ChangeData(WindowSize);
//	UI_Control_Manager -> UpdateSize(WindowSize);
}

void ClickFunc(ClickArgs args)
{
	//UI_Control_Manager -> RelayClick(params);
	(void)args;
}
void ScrollFunc(ScrollArgs args)
{
	//std::cout << "Scroll " << params.X << ' ' << params.Y << '\n';
	(void)args;
}
void MoveFunc(MoveArgs args)
{
	//std::cout << "Move " << params.Absolute << '\n';
	(void)args;
}
void DragFunc(DragArgs args)
{
	//UI_Control_Manager -> RelayCursorDrag(params);
	(void)args;

}

void KeyFunc(KeyArgs args)
{
	//UI_Control_Manager -> RelayKey(params);
	(void)args;
}
void TextFunc(TextArgs args)
{
	//UI_Control_Manager -> RelayText(params);
	(void)args;
}



int Main()
{
	window.InitCallBack.Assign(this, &MainContext::InitRun);
	window.FreeCallBack.Assign(this, &MainContext::FreeRun);
	window.FrameCallBack.Assign(this, &MainContext::Frame);
	window.ResizeCallBack.Assign(this, &MainContext::Resize);

	window.KeyBoardManager.CallBack_KeyEvent.Assign(this, &MainContext::KeyFunc);
	window.KeyBoardManager.CallBack_TextEvent.Assign(this, &MainContext::TextFunc);

	window.MouseManager.Callback_ClickEvent.Assign(this, &MainContext::ClickFunc);
	window.MouseManager.Callback_ScrollEvent.Assign(this, &MainContext::ScrollFunc);
	window.MouseManager.Callback_MoveEvent.Assign(this, &MainContext::MoveFunc);
	window.MouseManager.Callback_DragEvent.Assign(this, &MainContext::DragFunc);

	window.DefaultColor = ColorF4(0.875f, 0.875f, 0.875f);

	window.Create();
	Debug::Log << "<<<< Run Window" << Debug::Done;
	window.Run();
	Debug::Log << ">>>> Run Window" << Debug::Done;
	window.Delete();

	return 0;
}
};



int main(int argc, char * argv[])
{
	std::cout << "int main() ...\n";
	int ret = -1;
	Debug::NewFileInDir(DirectoryInfo("./logs/"));
	if (argc > 0)	{ Debug::Log << argv[0] << Debug::Done; }
	else			{ Debug::Log << "NoName" << Debug::Done; }
	if (glfwInit() == 0) { std::cout << "GLFW Init Failed\n"; return -1; }
	{
		try
		{
			MainContext context;
			ret = context.Main();
		}
		catch (std::exception & ex)
		{ Debug::Log << "Error: " << ex.what() << Debug::Done; }
		catch (...)
		{ Debug::Log << "Error: " << "Unknown" << Debug::Done; }
	}
	glfwTerminate();
	Debug::Log << "main() return " << ret << Debug::Done;
	return ret;
}

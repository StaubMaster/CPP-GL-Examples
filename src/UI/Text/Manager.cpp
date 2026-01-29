#include "Manager.hpp"

#include "DataInclude.hpp"

#include "Graphics/Shader/Code.hpp"

#include "DirectoryInfo.hpp"
#include "FileInfo.hpp"
#include "Image.hpp"

#include "DataShow.hpp"
#include <iostream>



UI::Text::Manager::Manager() :
	Shader(),
	BufferArray(),
	Main_Data_Container(),
	Inst_Data_Container()
{
	std::cout << "  ++++  " << "UI::Text::Manager::Manager()" << '\n';

	//TextFont = Font::Parse(text_dir.File("Font0.atlas"));
	//std::cout << "Font" << ' ' << "Default" << ' ' << (TextFont -> DefaultCharacter.Box.Min) << ' ' << (TextFont -> DefaultCharacter.Box.Max) << '\n';
	/*for (unsigned int i = 0; i < TextFont -> Characters.Count(); i++)
	{
		std::cout << "Font" << ' ' << (TextFont -> Characters[i].Code) << ' ' << (TextFont -> Characters[i].Box.Min) << ' ' << (TextFont -> Characters[i].Box.Max) << '\n';
	}*/
	//Pallet_Texture.Create();
	//Pallet_Texture.Bind();
	//Pallet_Texture.Assign(TextFont -> AtlasTexture);

	//Image * img = image_dir.File("Text_16x8_32x32.png").LoadImagePNG();
	//Image * img = Image::Missing();
	//Pallet_Texture = new Texture::T2DArray(img);
	//delete img;

	Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(-1, -1)));
	Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(-1, +1)));
	Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(+1, -1)));
	Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(+1, -1)));
	Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(-1, +1)));
	Main_Data_Container.Insert(UI::Text::Main_Data(Point2D(+1, +1)));
}
UI::Text::Manager::~Manager()
{
	std::cout << "  ----  " << "UI::Text::Manager::~Manager()" << '\n';

	BufferArray.Delete();
	Shader.Delete();

	Pallet_Texture.Delete();
	delete TextFont;
}



void UI::Text::Manager::Draw()
{
	if (!Inst_Data_Container.IsCompact())
	{
		Inst_Data_Container.CompactHere();
	}

	BufferArray.Bind();
	BufferArray.Main.Change(Main_Data_Container);
	BufferArray.Inst.Change(Inst_Data_Container);

	Shader.Bind();
	Pallet_Texture.Bind();
	BufferArray.Bind();
	BufferArray.Draw();
}

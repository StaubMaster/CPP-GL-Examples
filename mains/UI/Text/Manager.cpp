#include "Manager.hpp"

#include "DataInclude.hpp"

#include "DirectoryContext.hpp"
#include "FileContext.hpp"
#include "Format/Image.hpp"

#include "OpenGL/openGL.h"
#include <iostream>



UI::Text::Manager::Manager(const DirectoryContext & shader_dir, const DirectoryContext & image_dir) :
	Shader(shader_dir),
	BufferArray(),
	Main_Data_Container(),
	Inst_Data_Container()
{
	std::cout << "  ++++  " << "UI::Text::Manager::Manager()" << '\n';

	Image * img = image_dir.File("Text_16_8.png").LoadImagePNG();
	Pallet_Texture = new Texture::T2DArray(img);
	delete img;

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

	delete Pallet_Texture;
}



Point2D UI::Text::Manager::CharToTextCoord(int c)
{
	if (c >= '0' && c <= '9') { return Point2D(c - '0' ,0); }
	if (c >= 'A' && c <= 'M') { return Point2D(c - 'A' ,1); }
	if (c >= 'N' && c <= 'Z') { return Point2D(c - 'N' ,2); }
	if (c >= 'a' && c <= 'm') { return Point2D(c - 'a' ,3); }
	if (c >= 'n' && c <= 'z') { return Point2D(c - 'n' ,4); }
	if (c == '+') { return Point2D(10 ,0); }
	if (c == '-') { return Point2D(11 ,0); }
	if (c == '*') { return Point2D(12 ,0); }
	if (c == '/') { return Point2D(13 ,0); }
	if (c == '=') { return Point2D(13 ,2); }
	if (c == '<') { return Point2D(14 ,2); }
	if (c == '>') { return Point2D(15 ,2); }
	return Point2D(15, 0);
}

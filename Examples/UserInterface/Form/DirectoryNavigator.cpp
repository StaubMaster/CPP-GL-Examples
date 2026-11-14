#include "Form/DirectoryNavigator.hpp"



DirectoryNavigator::~DirectoryNavigator()
{ }
DirectoryNavigator::DirectoryNavigator()
	: UI::Control::Form()
{
	//float x, y0, y1;

	//DirectoryText.Anchor.X.AnchorMarginBoth(0, 0);
	//y0 = DirectoryText.Anchor.Y.AnchorMarginMin(0);
	DirectoryText.Make_Anchor_X_Both(nullptr, nullptr);
	DirectoryText.Make_Anchor_Y_Min(nullptr);

	//x = GoChild.Anchor.X.AnchorMarginMax(0, 120);
	//y1 = GoChild.Anchor.Y.AnchorMarginMax(0);
	GoChild.Make_Anchor_X_Max(nullptr, 120);
	GoChild.Make_Anchor_Y_Max(nullptr);
	GoChild.SetText("Child");

	//GoParent.Anchor.X.AnchorMarginMax(x, 140);
	//GoParent.Anchor.Y.AnchorMarginMax(0);
	GoParent.Make_Anchor_X_Max(&GoChild, 140);
	GoParent.Make_Anchor_Y_Max(nullptr);
	GoParent.SetText("Parent");
	GoParent.ClickFunc.Assign(this, &DirectoryNavigator::ClickGoParent);

	//FileList.Anchor.X.AnchorMarginBoth(0, 0);
	//FileList.Anchor.Y.AnchorMarginBoth(y0, y1);
	FileList.Make_Anchor_X_Both(nullptr, nullptr);
	FileList.Make_Anchor_Y_Both(&DirectoryText, &GoParent);
	FileList.ItemFunc.Assign(this, &DirectoryNavigator::ClickItem);

	ChildInsert(DirectoryText);
	ChildInsert(FileList);
	ChildInsert(GoParent);
	ChildInsert(GoChild);
}



#include <sstream>

void DirectoryNavigator::Change(const DirectoryInfo & dir)
{
	Directory = dir;
	DirectoryText.SetText(Directory.Path.ToString());

	FileList.ItemsClear();

	//Directorys = Directory.Directorys();
	/*for (unsigned int i = 0; i < Directorys.Length(); i++)
	{
		std::stringstream ss;
		ss << "D: " << Directorys[i].Name();
		FileList.ItemNew(ss.str().c_str(), &Directorys[i]);
	}*/

	//Files = Directory.Files();
	/*for (unsigned int i = 0; i < Files.Length(); i++)
	{
		std::stringstream ss;
		ss << "F: " << Files[i].Name();
		FileList.ItemNew(ss.str().c_str(), &Files[i]);
	}*/

	Infos = Directory.Children();
	for (unsigned int i = 0; i < Infos.Length(); i++)
	{
		std::stringstream ss;
		if (Infos[i].IsFile()) { ss << "F: "; }
		else if (Infos[i].IsDirectory()) { ss << "D: "; }
		else { ss << "N: "; }
		ss << Infos[i].Name();
		FileList.ItemNew(ss.str().c_str(), &Infos[i]);
	}
}

#include <iostream>
#include <string.h>
void DirectoryNavigator::ClickItem(const UI::Control::ListBox::Item & item)
{
	FileSystemInfo & info = *((FileSystemInfo*)item.Object);

	if (info.IsDirectory())
	{
		std::cout << "Directory: " << info << '\n';
		Change(info.ToDirectory());
	}
	else if (info.IsFile())
	{
		std::cout << "File: " << info << '\n';
	}
	else
	{
		std::cout << "Unknown: " << info << '\n';
	}

	/*if (i < Directorys.Length())
	{
		std::cout << "Dir: " << Directorys[i] << '\n';
	}
	else
	{
		i -= Directorys.Length();
		if (i < Files.Length())
		{
			std::cout << "File: " << Files[i] << '\n';
		}
		else
		{
			std::cout << "Unknown:\n";
		}
	}*/
}

#include "User/MouseArgs.hpp"
void DirectoryNavigator::ClickGoParent(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (Directory.HasParent())
	{
		Change(Directory.Parent());
	}
}

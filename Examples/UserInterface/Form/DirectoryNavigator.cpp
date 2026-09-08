#include "Form/DirectoryNavigator.hpp"



DirectoryNavigator::~DirectoryNavigator()
{ }
DirectoryNavigator::DirectoryNavigator()
	: UI::Control::Form()
{
	DirectoryText.Anchor.X.AnchorBoth(0, 0);
	DirectoryText.Anchor.Y.AnchorMin(0);

	GoChild.Anchor.X.AnchorMax(0, 120);
	GoChild.Anchor.Y.AnchorMax(0);
	GoChild.SetText("Child");

	GoParent.Anchor.X.AnchorMax(GoChild.Anchor.X.GetMaxSize(), 140);
	GoParent.Anchor.Y.AnchorMax(0);
	GoParent.SetText("Parent");
	GoParent.ClickFunc.Assign(this, &DirectoryNavigator::ClickGoParent);

	FileList.Anchor.X.AnchorBoth(0, 0);
	FileList.Anchor.Y.AnchorBoth(DirectoryText.Anchor.Y.GetMinSize(), GoChild.Anchor.Y.GetMaxSize());
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

void DirectoryNavigator::ClickGoParent(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (Directory.HasParent())
	{
		Change(Directory.Parent());
	}
}

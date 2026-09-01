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

	Directorys = Directory.Directorys();
	/*for (unsigned int i = 0; i < Directorys.Length(); i++)
	{
		std::stringstream ss;
		ss << "D: " << Directorys[i].Name();
		FileList.ItemNew(ss.str().c_str(), &Directorys[i]);
	}*/

	Files = Directory.Files();
	/*for (unsigned int i = 0; i < Files.Length(); i++)
	{
		std::stringstream ss;
		ss << "F: " << Files[i].Name();
		FileList.ItemNew(ss.str().c_str(), &Files[i]);
	}*/

	Container::Array<FileSystemInfo> infos = Directory.Children();
	for (unsigned int i = 0; i < infos.Length(); i++)
	{
		std::stringstream ss;
		if (infos[i].IsFile()) { ss << "F: "; }
		else if (infos[i].IsDirectory()) { ss << "D: "; }
		else { ss << "N: "; }
		ss << infos[i].Name();
		FileList.ItemNew(ss.str().c_str(), &infos[i]);
	}
}

void DirectoryNavigator::BoxUpdate()
{
	Base::BoxUpdate();
	//AutoAnchorUpdateRequest();
	//FileList.Content.AutoAnchorUpdateRequest();
	AutoAnchorUpdate();
	FileList.Content.AutoAnchorUpdate();
}



void DirectoryNavigator::ClickGoParent(ClickArgs args)
{
	if (args.Action != Action::Press) { return; }
	if (Directory.HasParent())
	{
		Change(Directory.Parent());
	}
}

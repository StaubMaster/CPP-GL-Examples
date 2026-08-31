#include "Form/DirectoryNavigator.hpp"



DirectoryNavigator::~DirectoryNavigator()
{ }
DirectoryNavigator::DirectoryNavigator()
	: UI::Control::Form()
{
	DirectoryText.Anchor.X.AnchorBoth(0, 0);
	DirectoryText.Anchor.Y.AnchorMin(0);

	GoChild.Anchor.X.AnchorMax(0);
	GoChild.Anchor.Y.AnchorMax(0);
	GoChild.SetText("Child");

	GoParent.Anchor.X.AnchorMax(GoChild.Anchor.X.GetMaxSize());
	GoParent.Anchor.Y.AnchorMax(0);
	GoParent.SetText("Parent");

	FileList.Anchor.X.AnchorBoth(0, 0);
	FileList.Anchor.Y.AnchorBoth(DirectoryText.Anchor.Y.GetMinSize(), GoChild.Anchor.Y.GetMaxSize());

	ChildInsert(DirectoryText);
	ChildInsert(FileList);
	ChildInsert(GoParent);
	ChildInsert(GoChild);
}



#include <vector>
#include <sstream>

void DirectoryNavigator::Change(const DirectoryInfo & dir)
{
	Directory = dir;
	DirectoryText.SetText(Directory.Path.ToString());

	FileList.ItemsClear();

	std::vector<DirectoryInfo> dirs = Directory.Directorys();
	Directorys.NewLength(dirs.size());
	for (unsigned int i = 0; i < Directorys.Length(); i++)
	{
		Directorys[i] = dirs[i];
		std::stringstream ss;
		ss << "D: " << Directorys[i].Name();
		FileList.ItemNew(ss.str().c_str(), &Directorys[i]);
	}

	//std::vector<FileInfo> files = Directory.Files();
}

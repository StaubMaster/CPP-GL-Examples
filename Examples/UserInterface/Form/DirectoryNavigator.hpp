#ifndef  DIRECTORY_NAVIGATOR_HPP
# define DIRECTORY_NAVIGATOR_HPP

# include "DirectoryInfo.hpp"
# include "FileInfo.hpp"
# include "FileSystemInfo.hpp"

# include "Generics/Container/Array.hpp"

# include "Control/_Include.hpp"

/* ListBox
	Items need to be selectable
*/

class DirectoryNavigator : public UI::Control_::Form
{
	public:
	DirectoryInfo						Directory;
	//Container::Array<DirectoryInfo>		Directorys;
	//Container::Array<FileInfo>			Files;
	Container::Array<FileSystemInfo>	Infos;

	public:
	UI::Control_::TextBox	DirectoryText;
	UI::Control_::ListBox	FileList;
	UI::Control_::Button	GoParent;
	UI::Control_::Button	GoChild;

	public:
	~DirectoryNavigator();
	DirectoryNavigator();

	public:
	void	Change(const DirectoryInfo & dir);

	private:
	void	ClickItem(const UI::Control_::ListBox::Item & item);

	public:
	void	ClickGoParent(ClickArgs args);
};

#endif
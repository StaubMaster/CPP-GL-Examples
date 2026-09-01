#ifndef  DIRECTORY_NAVIGATOR_HPP
# define DIRECTORY_NAVIGATOR_HPP

# include "DirectoryInfo.hpp"
# include "FileInfo.hpp"

# include "Generics/Container/Array.hpp"

# include "Control/_Include.hpp"

/* ListBox
	Items need to be selectable
*/

class DirectoryNavigator : public UI::Control::Form
{
	public:
	DirectoryInfo						Directory;
	Container::Array<DirectoryInfo>		Directorys;
	Container::Array<FileInfo>			Files;

	public:
	UI::Control::TextBox	DirectoryText;
	UI::Control::ListBox	FileList;
	UI::Control::Button		GoParent;
	UI::Control::Button		GoChild;

	public:
	~DirectoryNavigator();
	DirectoryNavigator();

	public:
	void	Change(const DirectoryInfo & dir);

	public:
	void	BoxUpdate() override;

	public:
	void	ClickGoParent(ClickArgs args);
};

#endif
#include "FileSystemInfo.hpp"

#include <iostream>



FileSystemInfo::FileSystemInfo(const char * path) :
	FileSystemStat(),
	Path(path),
	_OriginalPath(path)
{
	FileSystemStat::Refresh(Path.ToString());
}
FileSystemInfo::FileSystemInfo(const std::string & path) :
	FileSystemStat(),
	Path(path.c_str()),
	_OriginalPath(path)
{
	FileSystemStat::Refresh(Path.ToString());
}
FileSystemInfo::FileSystemInfo(const FilePath & path) :
	FileSystemStat(),
	Path(path),
	_OriginalPath(path.ToString())
{
	FileSystemStat::Refresh(Path.ToString());
}



void FileSystemInfo::Refresh()
{
	FileSystemStat::Refresh(Path.ToString());
}
bool FileSystemInfo::Exists() const
{
	return Valid; 
}
std::string FileSystemInfo::OriginalPath() const
{
	return _OriginalPath;
}
std::string FileSystemInfo::Name() const
{
	return std::string(Path.Name());
}



#include "FileInfo.hpp"
#include "DirectoryInfo.hpp"

bool FileSystemInfo::IsFile() const
{
	return Mode.IsFile();
}
FileInfo FileSystemInfo::ToFile() const
{
	return FileInfo(OriginalPath());
}
bool FileSystemInfo::IsDirectory() const
{
	return Mode.IsDirectory();
}
DirectoryInfo FileSystemInfo::ToDirectory() const
{
	return DirectoryInfo(OriginalPath());
}



#include <iostream>
std::ostream & operator<<(std::ostream & o, const FileSystemInfo & obj)
{
	o << obj.Path;
	if (obj.IsDirectory())
	{
		o << "/"; // use Slash from FilePath ?
	}
	//o << '\n';
	return o;
}

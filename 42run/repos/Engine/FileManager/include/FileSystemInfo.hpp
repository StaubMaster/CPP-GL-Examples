#ifndef  FILE_SYSTEM_INFO_HPP
# define FILE_SYSTEM_INFO_HPP

# include "FileSystemStat.hpp"
# include "FilePath.hpp"

# include <string>

class FileInfo;
class DirectoryInfo;

class FileSystemInfo : public FileSystemStat
{
	public:		FilePath	Path;
	private:	std::string	_OriginalPath;

	public:
	~FileSystemInfo() = default;
	FileSystemInfo() = default;
	FileSystemInfo(const FileSystemInfo & other) = default;
	FileSystemInfo & operator=(const FileSystemInfo & other) = default;

	public:
	FileSystemInfo(const char * path);
	FileSystemInfo(const std::string & path);
	FileSystemInfo(const FilePath & path);

	public:
	void	Refresh();
	bool	Exists() const;
	std::string		OriginalPath() const;
	std::string		Name() const;

	public:
	bool				IsFile() const;
	FileInfo			ToFile() const;
	bool				IsDirectory() const;
	DirectoryInfo		ToDirectory() const;
};

# include <iosfwd>
std::ostream & operator<<(std::ostream & o, const FileSystemInfo & obj);

#endif
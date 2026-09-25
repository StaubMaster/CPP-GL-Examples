#ifndef  DIRECTORY_INFO_HPP
# define DIRECTORY_INFO_HPP

# include "FileSystemInfo.hpp"

# include <string>
# include <exception>

// forward define this ?
# include "Generics/Container/Array.hpp"

class FileInfo;

class DirectoryInfo : public FileSystemInfo
{
	public:
	~DirectoryInfo() = default;
	DirectoryInfo() = default;
	DirectoryInfo(const DirectoryInfo & other) = default;
	DirectoryInfo & operator=(const DirectoryInfo & other) = default;

	public:
	DirectoryInfo(const char * path);
	DirectoryInfo(const std::string & path);
	DirectoryInfo(const FilePath & path);

	public:
	static DirectoryInfo Here();

	public:
	bool	IsEmpty() const;
	void	Delete();
	void	Create();

	public:
	bool	HasParent() const;
	bool	HasChild(const char * name) const;
	bool	HasChild(const std::string & name) const;
	bool	HasFile(const char * name) const;
	bool	HasFile(const std::string & name) const;
	bool	HasDirectory(const char * name) const;
	bool	HasDirectory(const std::string & name) const;

	public:
	DirectoryInfo	Parent() const;
	FileSystemInfo	Child(const char * name) const;
	FileSystemInfo	Child(const std::string & name) const;
	FileInfo		File(const char * name) const;
	FileInfo		File(const std::string & name) const;
	DirectoryInfo	Directory(const char * name) const;
	DirectoryInfo	Directory(const std::string & name) const;

	public:
	Container::Array<FileSystemInfo>	Children() const;
	Container::Array<FileInfo>			Files() const;
	Container::Array<DirectoryInfo>		Directorys() const;
};

#endif
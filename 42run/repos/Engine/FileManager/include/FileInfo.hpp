#ifndef  FILE_INFO_HPP
# define FILE_INFO_HPP

# include "FileSystemInfo.hpp"

# include <string>

class DirectoryInfo;
class Image;
class ByteBlock;

class FileInfo : public FileSystemInfo
{
	public:
	~FileInfo() = default;
	FileInfo() = default;
	FileInfo(const FileInfo & other) = default;
	FileInfo & operator=(const FileInfo & other) = default;

	public:
	FileInfo(const char * path);
	FileInfo(const std::string & path);
	FileInfo(const FilePath & path);
	DirectoryInfo ToDirectory() const;

	public:
	void	Delete();
	void	Create();

	public:
	DirectoryInfo	Directory() const;
	std::string		Extension() const;



	public:
	ByteBlock	LoadBytes() const;
	void		SaveBytes(const ByteBlock & block) const;

	std::string		LoadText() const;
	void			SaveText(const std::string & text) const;

	// should Save be non-constant ?
	// maybe Update FileInfo ?

	Image	LoadImage(bool debug = false) const;
	void	SaveImage(const Image & img) const;
};

#endif
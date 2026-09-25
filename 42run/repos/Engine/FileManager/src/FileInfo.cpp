#include "FileInfo.hpp"
#include "FileExceptions.hpp"
#include "DirectoryInfo.hpp"

#include "Image.hpp"
#include "FileParsing/ByteBlock.hpp"
#include "FileFormat/PNG/PNG.hpp"
#include "FileFormat/BitMap/BitMap.hpp"

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

#include <iostream>



FileInfo::FileInfo(const char * path)
	: FileSystemInfo(path)
{ }
FileInfo::FileInfo(const std::string & path)
	: FileSystemInfo(path)
{ }
FileInfo::FileInfo(const FilePath & path)
	: FileSystemInfo(path)
{ }





void FileInfo::Delete()
{
	if (!Exists()) { throw FileNotFound(Path); }
	if (!Mode.IsFile()) { throw FileIsNotFile(Path); }

	//FilePath path = Path.ToAbsolute();
	//std::cout << "Delete File: " << Mode << ' ' << Path << '\n';
	if (unlink(Path.ToString()) != 0)
	{
		throw FileProblem(Path, "unlink");
	}

	Refresh();
	//std::cout << "File: " << Mode << ' ' << Path << '\n';
	//std::cout << "File Info\n" << *this << '\n';
}
void FileInfo::Create()
{
	if (Exists() && !Mode.IsFile()) { throw FileIsNotFile(Path); }

	DirectoryInfo parent = DirectoryInfo(Path.Parent());
	if (!parent.Exists() && !parent.Path.IsNone())
	{
		//std::cout << "needs Parent '" << parent.Path << "'\n";
		parent.Create();
	}

	FileMode mode;
	//FilePath path = Path.ToAbsolute();
	//std::cout << "Create File: " << mode << ' ' << Path << '\n';
	int fd = creat(Path.ToString(), mode.Data);
	if (fd <= -1)
	{
		throw FileProblem(Path, "creat");
	}
	if (close(fd) != 0)
	{
		throw FileProblem(Path, "close");
	}

	mode.AllAll(true);
	if (chmod(Path.ToString(), mode.Data) != 0)
	{
		throw FileProblem(Path, "chmod");
	}

	Refresh();
	//std::cout << "File: " << Mode << ' ' << Path << '\n';
	//std::cout << "File Info\n" << *this << '\n';
}





DirectoryInfo FileInfo::Directory() const
{
	return DirectoryInfo(Path.Parent());
}
std::string FileInfo::Extension() const
{
	std::string str(Path.Name());
	size_t idx = str.find_last_of('.');
	if (idx != std::string::npos)
	{
		return str.substr(idx);
	}
	return std::string();
}





ByteBlock FileInfo::LoadBytes() const
{
	if (!Exists()) { throw FileNotFound(Path); }
	if (!Mode.IsFile()) { throw FileIsNotFile(Path); }

	return ByteBlock(LoadText());
}
void FileInfo::SaveBytes(const ByteBlock & block) const
{
	if (Exists()) { throw FileProblem(Path, "File already exists."); }

	std::ofstream stream(Path.ToString(), std::ios::binary);
	if (!stream.is_open())
	{
		throw FileProblem(Path);
	}

	stream.write((const char *)block.Data(), block.Length());
}





// this should be in LoadBytes
// LoadText should not have ios::binary
std::string FileInfo::LoadText() const
{
	if (!Exists()) { throw FileNotFound(Path); }
	if (!Mode.IsFile()) { throw FileIsNotFile(Path); }

	std::ifstream stream(Path.ToString(), std::ios::binary);
	if (!stream.is_open()) { throw FileProblem(Path); }

	const int	block_size = 1024;
	char		block_data[block_size];

	std::string	text;

	stream.read(block_data, block_size);
	while (!stream.eof())
	{
		text += std::string(block_data, block_size);
		stream.read(block_data, block_size);
	}
	text += std::string(block_data, stream.gcount());

	return (text);
}
void FileInfo::SaveText(const std::string & text) const
{
	if (Exists()) { throw FileProblem(Path, "File already exists."); }

	SaveBytes(ByteBlock(text));
}





Image FileInfo::LoadImage(bool debug) const
{
	if (!Exists()) { throw FileNotFound(Path); }
	if (!Mode.IsFile()) { throw FileIsNotFile(Path); }

	std::string extension = Extension();
	if (extension == ".png") { return PNG::Load(*this, debug); }
	if (extension == ".PNG") { return PNG::Load(*this, debug); }
	if (extension == ".bmp") { return BitMap::Load(*this); }
	if (extension == ".dib") { return BitMap::Load(*this); }
	throw InvalidExtension(extension);
}
void FileInfo::SaveImage(const Image & img) const
{
	if (Exists()) { throw FileProblem(Path, "File already exists."); }

	std::string extension = Extension();
//	if (extension == ".png") { return PNG::Save(*this, debug); }
//	if (extension == ".PNG") { return PNG::Save(*this, debug); }
//	if (extension == ".bmp") { return BitMap::Save(*this, img); }
//	if (extension == ".dib") { return BitMap::Save(*this, img); }
	throw InvalidExtension(extension);
	(void)img;
}

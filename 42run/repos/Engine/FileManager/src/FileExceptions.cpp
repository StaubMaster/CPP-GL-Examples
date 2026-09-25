#include "FileExceptions.hpp"
#include "FilePath.hpp"

#include <sstream>
#include <errno.h>
#include <string.h>



InvalidPath::InvalidPath(const FilePath & path)
{
	std::stringstream ss;
	ss << "Invalid Path " << path.ToString() << ".";
	Text = ss.str();
}
InvalidExtension::InvalidExtension(const std::string & extention)
{
	std::stringstream ss;
	ss << "Invalid Extension " << extention << ".";
	Text = ss.str();
}



FileProblem::FileProblem(const FilePath & path)
{
	std::stringstream ss;
	ss << "Problem with File: " << path.ToString() << ".";
	if (errno != 0) { ss << " Errno: " << strerror(errno) << "."; }
	Text = ss.str();
}
FileProblem::FileProblem(const FilePath & path, const char * func)
{
	std::stringstream ss;
	ss << "Problem with File: " << path.ToString() << ".";
	ss << " Function: " << func << ".";
	if (errno != 0) { ss << " Errno: " << strerror(errno) << "."; }
	Text = ss.str();
}
FileNotFound::FileNotFound(const FilePath & path)
{
	std::stringstream ss;
	ss << "File " << path.ToString() << " not found.";
	Text = ss.str();
}
FileIsNotFile::FileIsNotFile(const FilePath & path)
{
	std::stringstream ss;
	ss << "File " << path.ToString() << " is not a File.";
	Text = ss.str();
}



DirectoryProblem::DirectoryProblem(const FilePath & path)
{
	std::stringstream ss;
	ss << "Problem with Directory: " << path.ToString() << ".";
	if (errno != 0) { ss << " Errno: " << strerror(errno) << "."; }
	Text = ss.str();
}
DirectoryProblem::DirectoryProblem(const FilePath & path, const char * func)
{
	std::stringstream ss;
	ss << "Problem with Directory: " << path.ToString() << ".";
	ss << " Function: " << func << ".";
	if (errno != 0) { ss << " Errno: " << strerror(errno) << "."; }
	Text = ss.str();
}
DirectoryNotFound::DirectoryNotFound(const FilePath & path)
{
	std::stringstream ss;
	ss << "Directory " << path.ToString() << " not found.";
	Text = ss.str();
}
DirectoryIsNotDirectory::DirectoryIsNotDirectory(const FilePath & path)
{
	std::stringstream ss;
	ss << "Directory " << path.ToString() << " is not a Directory.";
	Text = ss.str();
}

#ifndef  FILE_EXCEPTIONS_HPP
# define FILE_EXCEPTIONS_HPP

# include "TextExceptionBase.hpp"

class FilePath;



class InvalidPath : public TextExceptionBase
{
	public: InvalidPath(const FilePath & path);
};
class InvalidExtension : public TextExceptionBase
{
	public: InvalidExtension(const std::string & extention);
};



class FileProblem : public TextExceptionBase
{
	public: FileProblem(const FilePath & path);
	public: FileProblem(const FilePath & path, const char * func);
};
class FileNotFound : public TextExceptionBase
{
	public: FileNotFound(const FilePath & path);
};
class FileIsNotFile : public TextExceptionBase
{
	public: FileIsNotFile(const FilePath & path);
};



class DirectoryProblem : public TextExceptionBase
{
	public: DirectoryProblem(const FilePath & path);
	public: DirectoryProblem(const FilePath & path, const char * func);
};
class DirectoryNotFound : public TextExceptionBase
{
	public: DirectoryNotFound(const FilePath & path);
};
class DirectoryIsNotDirectory : public TextExceptionBase
{
	public: DirectoryIsNotDirectory(const FilePath & path);
};

#endif
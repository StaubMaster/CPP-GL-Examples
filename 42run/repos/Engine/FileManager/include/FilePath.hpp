#ifndef  FILE_PATH_HPP
# define FILE_PATH_HPP

# include "FilePathSegmentCollection.hpp"

# include <iosfwd>

class FilePath
{
	//private:
	public:
	FilePathSegmentCollection	Segments;
	char *						PathString;

	public:
	~FilePath();
	FilePath();
	FilePath(const FilePath & other);
	FilePath & operator=(const FilePath & other);

	public:
	FilePath(const char * path);

	public:
	const char *	ToString() const;
	const char *	Name() const;

	public:
	static FilePath		Here();

	bool	IsNone() const;
	bool	IsAbsolute() const;
	bool	IsRelative() const;

	FilePath	ToAbsolute() const;
	FilePath	ToRelative(const FilePath & root) const;

	public:
	FilePath	Parent() const;
	FilePath	Child(const char * path) const;
	FilePath	Child(const FilePath & path) const;
};

std::ostream & operator<<(std::ostream & o, const FilePath & val);

#endif
#include "FilePath.hpp"

//#include <sstream>
#include <dirent.h>
#include <iostream>



#if defined(_WIN32)
# include <windows.h>
# define SLASH '\\'
#endif

#if defined(__APPLE__)
# include <unistd.h>
# define SLASH '/'
#endif

#if defined(__linux__)
# include <unistd.h>
# define SLASH '/'
#endif



FilePath::FilePath() :
	Segments(),
	PathString(0)
{ }
FilePath::FilePath(const char * path) :
	Segments(FilePathSegmentCollection::Split(path)),
	PathString(Segments.ToString())
{ }
FilePath::~FilePath()
{
	delete[] PathString;
}

FilePath::FilePath(const FilePath & other) :
	Segments(other.Segments),
	PathString(Segments.ToString())
{ }
FilePath & FilePath::operator=(const FilePath & other)
{
	delete[] PathString;
	Segments = other.Segments;
	PathString = Segments.ToString();
	return *this;
}



const char * FilePath::ToString() const
{
	return PathString;
}
const char * FilePath::Name() const
{
	if (Segments.Count() == 0) { return 0; }
	return Segments[Segments.Count() - 1].String;
}



FilePath FilePath::Here()
{
#if defined(_WIN32)
	TCHAR path[MAX_PATH];
	//DWORD len = GetCurrentDirectory(MAX_PATH, buf);
	if (GetCurrentDirectory(MAX_PATH, path) == 0)
	{
		std::cout << "Error getting current Dir\n";
	}
	return FilePath(path);
#endif

#if defined(__APPLE__)
	char path[PATH_MAX];
	if (getwd(path) == NULL)
	{
		std::cout << "Error getting current Dir\n";
	}
	return FilePath(path);
#endif

#if defined(__linux__)
	char path[PATH_MAX];
	if (getcwd(path, PATH_MAX) == NULL)
	{
		std::cout << "Error getting current Dir\n";
	}
	return FilePath(path);
#endif
}



bool FilePath::IsNone() const
{
	return (Segments.Count() == 0);
}
/*bool FilePath::IsAbsolute() const
{
	const std::string & seg = Segments[0];
#if defined(_WIN32)
	if (seg.size() < 2) { return false; }
	if (!std::isalpha(seg[0])) { return false; }
	if (seg[1] != ':') { return false; }
#endif
#if defined(__APPLE__)
	if (!seg.empty()) { return false; }
#endif
	return true;
}*/
/*bool FilePath::IsRelative() const
{
	return !IsAbsolute();
}*/

FilePath FilePath::ToAbsolute() const
{
	//if (IsAbsolute()) { return FilePath(ToString()); }
	//return FilePath(Here().ToString() + SLASH + ToString());
	FilePath filepath;
	filepath.Segments = Here().Segments.Append(Segments);
	filepath.PathString = filepath.Segments.ToString();
	return filepath;
}
/*FilePath FilePath::ToRelative(const FilePath & root) const
{
	size_t i0 = 0;
	size_t i1 = 0;

	if (Segments[i0] == THIS_DIR) { i0++; }

	for (; i0 < Segments.size() && i1 < root.Segments.size(); i0++, i1++)
	{
		if (Segments[i0] != root.Segments[i1])
		{
			break;
		}
	}

	//FilePath path((root.Segments.size() - i0) + (Segments.size() - i1) + 1);
	FilePath path;

	path.Segments.push_back(THIS_DIR);

	for (; i1 < root.Segments.size(); i1++)
	{
		path.Segments.push_back(META_DIR);
	}

	for (; i0 < Segments.size(); i0++)
	{
		path.Segments.push_back(Segments[i0]);
	}

	return FilePath(path);
}*/



FilePath FilePath::Parent() const
{
	FilePath filepath;
	filepath.Segments = Segments.RemoveLast();
	filepath.PathString = filepath.Segments.ToString();
	return filepath;
}
FilePath FilePath::Child(const char * path) const
{
	FilePath filepath;
	filepath.Segments = Segments.Append(FilePathSegmentCollection::Split(path));
	filepath.PathString = filepath.Segments.ToString();
	return filepath;
}
FilePath FilePath::Child(const FilePath & path) const
{
	FilePath filepath;
	filepath.Segments = Segments.Append(path.Segments);
	filepath.PathString = filepath.Segments.ToString();
	return filepath;
}





std::ostream & operator<<(std::ostream & o, const FilePath & obj)
{
	const char * str = obj.ToString();
	if (str != 0) { o << str; }
	return o;
}

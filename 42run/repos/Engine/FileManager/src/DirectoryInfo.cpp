#include "DirectoryInfo.hpp"
#include "FileExceptions.hpp"
#include "FileInfo.hpp"

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <cctype>

#include <iostream>



DirectoryInfo::DirectoryInfo(const char * path)
	: FileSystemInfo(path)
{ }
DirectoryInfo::DirectoryInfo(const std::string & path)
	: FileSystemInfo(path)
{ }
DirectoryInfo::DirectoryInfo(const FilePath & path)
	: FileSystemInfo(path)
{ }

DirectoryInfo DirectoryInfo::Here()
{
	return DirectoryInfo(FilePath::Here());
}



bool DirectoryInfo::IsEmpty() const
{
	if (!Exists() || !IsDirectory())
	{
		throw DirectoryNotFound(Path);
	}

	DIR * dir = opendir(Path.ToString());
	if (dir == NULL)
	{
		throw DirectoryProblem(Path, "opendir");
	}

	bool empty = true;

	struct dirent * ent;
	ent = readdir(dir);
	while (ent != NULL)
	{
		std::string name = ent -> d_name;
		if (name != "." && name != "..")
		{
			empty = false;
			break;
		}
		ent = readdir(dir);
	}

	if (closedir(dir) != 0)
	{
		throw DirectoryProblem(Path, "closedir");
	}
	return empty;
}
void DirectoryInfo::Delete()
{
	if (!Exists()) { throw DirectoryNotFound(Path); }
	if (!IsDirectory()) { throw DirectoryIsNotDirectory(Path); }

	DIR * dir = opendir(Path.ToString());
	if (dir == NULL)
	{
		throw DirectoryProblem(Path, "opendir");
	}

	struct dirent * ent;
	ent = readdir(dir);
	while (ent != NULL)
	{
		std::string name = ent -> d_name;
		if (name != "." && name != "..")
		{
			FilePath path = Path.Child(ent -> d_name);
			FileSystemStat stat(path.ToString());
			if (stat.Mode.IsFile())
			{
				FileInfo file(path);
				file.Delete();
			}
			if (stat.Mode.IsDirectory())
			{
				DirectoryInfo directory(path);
				directory.Delete();
			}
		}
		ent = readdir(dir);
	}

	if (closedir(dir) != 0)
	{
		throw DirectoryProblem(Path, "closedir");
	}

	//std::cout << "Delete Directory: " << Mode << ' ' << Path << '\n';
	if (rmdir(Path.ToString()) != 0)
	{
		throw DirectoryProblem(Path, "rmdir");
	}

	Refresh();
	//std::cout << "Directory: " << Mode << ' ' << Path << '\n';
	//std::cout << "Directory Info\n" << *this << '\n';
}
void DirectoryInfo::Create()
{
	if (Exists() && !IsDirectory()) { throw DirectoryIsNotDirectory(Path); }

	if (Path.ToString()[0] == '\0')
	{
		throw DirectoryProblem(Path);
	}

	DirectoryInfo parent = Parent();
	if (!parent.Exists() && !parent.Path.IsNone())
	{
		parent.Create();
	}

	//std::cout << "Create Directory: " << Mode << ' ' << Path << '\n';
#if defined(_WIN32)
	if (mkdir(Path.ToString()) != 0)
#endif
#if defined(__APPLE__)
	FileMode mode;
	mode.AllAll(true);
	if (mkdir(Path.ToString(), mode.Data) != 0)
#endif
	{
		throw DirectoryProblem(Path, "mkdir");
	}

	Refresh();
	//std::cout << "Directory: " << Mode << ' ' << Path << '\n';
	//std::cout << "Directory Info\n" << *this << '\n';
}



bool DirectoryInfo::HasParent() const
{
	FileSystemInfo info(Path.Parent().ToString());
	return (info.Exists() && info.IsDirectory());
}
bool DirectoryInfo::HasChild(const char * name) const
{
	FileSystemInfo info(Path.Child(name).ToString());
	return (info.Exists());
}
bool DirectoryInfo::HasChild(const std::string & name) const
{
	FileSystemInfo info(Path.Child(name.c_str()).ToString());
	return (info.Exists());
}
bool DirectoryInfo::HasFile(const char * name) const
{
	FileSystemInfo info(Path.Child(name).ToString());
	return (info.Exists() && info.IsFile());
}
bool DirectoryInfo::HasFile(const std::string & name) const
{
	FileSystemInfo info(Path.Child(name.c_str()).ToString());
	return (info.Exists() && info.IsFile());
}
bool DirectoryInfo::HasDirectory(const char * name) const
{
	FileSystemInfo info(Path.Child(name).ToString());
	return (info.Exists() && info.IsDirectory());
}
bool DirectoryInfo::HasDirectory(const std::string & name) const
{
	FileSystemInfo info(Path.Child(name.c_str()).ToString());
	return (info.Exists() && info.IsDirectory());
}

DirectoryInfo DirectoryInfo::Parent() const
{
	return DirectoryInfo(Path.Parent().ToString());
}
FileSystemInfo DirectoryInfo::Child(const char * name) const
{
	return FileSystemInfo(Path.Child(name).ToString());
}
FileSystemInfo DirectoryInfo::Child(const std::string & name) const
{
	return FileSystemInfo(Path.Child(name.c_str()).ToString());
}
FileInfo DirectoryInfo::File(const char * name) const
{
	return FileInfo(Path.Child(name).ToString());
}
FileInfo DirectoryInfo::File(const std::string & name) const
{
	return FileInfo(Path.Child(name.c_str()).ToString());
}
DirectoryInfo DirectoryInfo::Directory(const char * name) const
{
	return DirectoryInfo(Path.Child(name).ToString());
}
DirectoryInfo DirectoryInfo::Directory(const std::string & name) const
{
	return DirectoryInfo(Path.Child(name.c_str()).ToString());
}



#include "Generics/Container/Binary.hpp"
Container::Array<FileSystemInfo> DirectoryInfo::Children() const
{
	if (!Exists()) { throw DirectoryNotFound(Path); }
	if (!IsDirectory()) { throw DirectoryIsNotDirectory(Path); }

	DIR * dir;
	struct dirent * ent;

	dir = opendir(Path.ToString());
	if (dir == NULL) { throw DirectoryProblem(Path, "opendir"); }

	Container::Binary<FileSystemInfo> children;

	ent = readdir(dir);
	while (ent != NULL)
	{
		children.Insert(FileSystemInfo(Path.Child(ent -> d_name)));
		ent = readdir(dir);
	}

	if (closedir(dir) != 0) { throw DirectoryProblem(Path, "closedir"); }

	return children.ToArray();
}
Container::Array<FileInfo> DirectoryInfo::Files() const
{
	if (!Exists()) { throw DirectoryNotFound(Path); }
	if (!IsDirectory()) { throw DirectoryIsNotDirectory(Path); }

	DIR * dir;
	struct dirent * ent;

	dir = opendir(Path.ToString());
	if (dir == NULL) { throw DirectoryProblem(Path, "opendir"); }

	Container::Binary<FileInfo> children;

	ent = readdir(dir);
	while (ent != NULL)
	{
		//if (ent -> d_type == DT_REG)
		FileSystemInfo info(Path.Child(ent -> d_name));
		if (info.IsFile())
		{
			children.Insert(info.ToFile());
		}
		ent = readdir(dir);
	}

	if (closedir(dir) != 0) { throw DirectoryProblem(Path, "closedir"); }

	return children.ToArray();
}
Container::Array<DirectoryInfo> DirectoryInfo::Directorys() const
{
	if (!Exists()) { throw DirectoryNotFound(Path); }
	if (!IsDirectory()) { throw DirectoryIsNotDirectory(Path); }

	DIR * dir;
	struct dirent * ent;

	dir = opendir(Path.ToString());
	if (dir == NULL) { throw DirectoryProblem(Path, "opendir"); }

	Container::Binary<DirectoryInfo> children;

	ent = readdir(dir);
	while (ent != NULL)
	{
		//if (ent -> d_type == DT_DIR)
		FileSystemInfo info(Path.Child(ent -> d_name));
		if (info.IsDirectory())
		{
			children.Insert(info.ToDirectory());
			//children.Insert(FilePath(ent -> d_name));
		}
		ent = readdir(dir);
	}

	if (closedir(dir) != 0) { throw DirectoryProblem(Path, "closedir"); }

	return children.ToArray();
}

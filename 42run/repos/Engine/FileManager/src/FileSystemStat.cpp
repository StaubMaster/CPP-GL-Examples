#include "FileSystemStat.hpp"

#include <unistd.h>



FileSystemStat::FileSystemStat(const char * path)
{
	if (access(path, 0) == 0)
	{
		struct stat sys_stat;
		Valid = (stat(path, &sys_stat) == 0);
		Mode = sys_stat.st_mode;
		Idone = sys_stat.st_ino;
		UserID = sys_stat.st_uid;
		GroupID = sys_stat.st_gid;
		DeviceID = sys_stat.st_dev;
		SpecialID = sys_stat.st_rdev;
		LinkCount = sys_stat.st_nlink;
		CreateTime = sys_stat.st_ctime;
		ModifyTime = sys_stat.st_mtime;
		AccessTime = sys_stat.st_atime;
		Size = sys_stat.st_size;;
	}
}
void FileSystemStat::Refresh(const char * path)
{
	if (access(path, 0) == 0)
	{
		struct stat sys_stat;
		Valid = (stat(path, &sys_stat) == 0);
		Mode = sys_stat.st_mode;
		Idone = sys_stat.st_ino;
		UserID = sys_stat.st_uid;
		GroupID = sys_stat.st_gid;
		DeviceID = sys_stat.st_dev;
		SpecialID = sys_stat.st_rdev;
		LinkCount = sys_stat.st_nlink;
		CreateTime = sys_stat.st_ctime;
		ModifyTime = sys_stat.st_mtime;
		AccessTime = sys_stat.st_atime;
		Size = sys_stat.st_size;;
	}
	else
	{
		Valid = false;
		Mode = FileMode();
		Idone = 0;
		UserID = 0;
		GroupID = 0;
		DeviceID = 0;
		SpecialID = 0;
		LinkCount = 0;
		CreateTime = 0;
		ModifyTime = 0;
		AccessTime = 0;
		Size = 0;
	}
}



#include <iostream>
std::ostream & operator<<(std::ostream & o, const FileSystemStat & obj)
{
	o << "Valid " << obj.Valid << '\n';
	o << "Mode " << obj.Mode << '\n';
	o << "Inode " << obj.Idone << '\n';
	o << "Links " << obj.LinkCount << '\n';
	o << "UserID " << obj.UserID << '\n';
	o << "GroupID " << obj.GroupID << '\n';
	o << "DeviceID " << obj.DeviceID << '\n';
	o << "SpecialID " << obj.SpecialID << '\n';
	o << "CreateTime " << obj.CreateTime << '\n';
	o << "ModifyTime " << obj.ModifyTime << '\n';
	o << "AccessTime " << obj.AccessTime << '\n';
	o << "Size " << obj.Size << '\n';
	return o;
}

#ifndef  FILE_SYSTEM_STAT_HPP
# define FILE_SYSTEM_STAT_HPP

# include "FileMode.hpp"

# include <sys/stat.h>

/*msys64\ucrt64\include\_mingw_stat64.h
  struct stat {
    _dev_t st_dev;
    _ino_t st_ino;
    unsigned short st_mode;
    short st_nlink;
    short st_uid;
    short st_gid;
    _dev_t st_rdev;
    _off_t st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
  };
*/
class FileSystemStat
{
	//	make this store the individual values
	//	only use struct stat for getting the data
	public:
	bool	Valid = false;

# if defined(_WIN32)
	FileMode	Mode;			//unsigned short st_mode;
	_ino_t		Idone = 0;		//_ino_t st_ino;
	short		UserID = 0;		//short st_uid;
	short		GroupID = 0;	//short st_gid;
	_dev_t		DeviceID = 0;	//_dev_t st_dev;
	_dev_t		SpecialID = 0;	//_dev_t st_rdev;
	short		LinkCount = 0;	//short st_nlink;
	time_t		CreateTime = 0;	//time_t st_ctime;
	time_t		ModifyTime = 0;	//time_t st_mtime;
	time_t		AccessTime = 0;	//time_t st_atime;
	_off_t		Size = 0;		//_off_t st_size;
	//struct stat sys_stat;
# endif

# if defined(__APPLE__)
	FileMode	Mode;			//unsigned short st_mode;
	ino_t		Idone = 0;		//_ino_t st_ino;
	short		UserID = 0;		//short st_uid;
	short		GroupID = 0;	//short st_gid;
	dev_t		DeviceID = 0;	//_dev_t st_dev;
	dev_t		SpecialID = 0;	//_dev_t st_rdev;
	short		LinkCount = 0;	//short st_nlink;
	time_t		CreateTime = 0;	//time_t st_ctime;
	time_t		ModifyTime = 0;	//time_t st_mtime;
	time_t		AccessTime = 0;	//time_t st_atime;
	off_t		Size = 0;		//_off_t st_size;
	//struct stat sys_stat;
# endif

# if defined(__linux__)
	FileMode	Mode;			//unsigned short st_mode;
	ino_t		Idone = 0;		//_ino_t st_ino;
	short		UserID = 0;		//short st_uid;
	short		GroupID = 0;	//short st_gid;
	dev_t		DeviceID = 0;	//_dev_t st_dev;
	dev_t		SpecialID = 0;	//_dev_t st_rdev;
	short		LinkCount = 0;	//short st_nlink;
	time_t		CreateTime = 0;	//time_t st_ctime;
	time_t		ModifyTime = 0;	//time_t st_mtime;
	time_t		AccessTime = 0;	//time_t st_atime;
	off_t		Size = 0;		//_off_t st_size;
	//struct stat sys_stat;
# endif

	public:
	~FileSystemStat() = default;
	FileSystemStat() = default;
	FileSystemStat(const FileSystemStat & other) = default;
	FileSystemStat & operator=(const FileSystemStat & other) = default;

	public:
	FileSystemStat(const char * path);

	protected:
	void	Refresh(const char * path);
};

std::ostream & operator<<(std::ostream & o, const FileSystemStat & obj);

#endif
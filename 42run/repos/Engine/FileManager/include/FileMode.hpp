#ifndef  FILE_MODE_HPP
# define FILE_MODE_HPP

//	Make this not a referance anymore
//	renname to UnixFileMode
//	make a UnixTime thing ?
class FileMode
{
	public:
	unsigned short Data = 0;

	// = default
	public:
	~FileMode() = default;
	FileMode() = default;
	FileMode(const FileMode & other) = default;
	FileMode & operator=(const FileMode & other) = default;

	public:
	FileMode(unsigned short data);

	public:
	bool	IsFile() const;
	bool	IsDirectory() const;

	public:
	bool	UserR() const;
	bool	UserW() const;
	bool	UserX() const;
	bool	UserAll() const;

	bool	GroupR() const;
	bool	GroupW() const;
	bool	GroupX() const;
	bool	GroupAll() const;

	bool	OtherR() const;
	bool	OtherW() const;
	bool	OtherX() const;
	bool	OtherAll() const;

	bool	AllR() const;
	bool	AllW() const;
	bool	AllX() const;
	bool	AllAll() const;

	public:
	void	UserR(bool val);
	void	UserW(bool val);
	void	UserX(bool val);
	void	UserAll(bool val);

	void	GroupR(bool val);
	void	GroupW(bool val);
	void	GroupX(bool val);
	void	GroupAll(bool val);

	void	OtherR(bool val);
	void	OtherW(bool val);
	void	OtherX(bool val);
	void	OtherAll(bool val);

	void	AllR(bool val);
	void	AllW(bool val);
	void	AllX(bool val);
	void	AllAll(bool val);
};

# include <iosfwd>
std::ostream & operator<<(std::ostream & o, const FileMode & val);

#endif

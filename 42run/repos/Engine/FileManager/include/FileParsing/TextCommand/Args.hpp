#ifndef  TEXT_COMMAND_ARGS_HPP
# define TEXT_COMMAND_ARGS_HPP

# include <string>
# include <vector>
# include <iosfwd>

namespace TextCommand
{
class Args
{
	private:
	unsigned int	_Count;
	std::string *	_Segments;

	public:
	bool			Empty() const;
	std::string		Name() const;
	unsigned int	Count() const;

	public:
	std::string		ToString(unsigned int idx) const;
	unsigned int	ToUInt32(unsigned int idx) const;
	int				ToInt32(unsigned int idx) const;
	float			ToFloat(unsigned int idx) const;

	public:
	~Args();
	Args();
	Args(const Args & other);
	Args & operator=(const Args & other);

	public:
	void	Split(const std::string & str);
};
};

std::ostream &	operator<<(std::ostream & o, const TextCommand::Args & obj);

#endif
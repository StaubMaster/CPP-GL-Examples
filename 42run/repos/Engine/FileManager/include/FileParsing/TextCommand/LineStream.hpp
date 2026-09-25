#ifndef  LINE_STREAM_HPP
# define LINE_STREAM_HPP

# include <string>
# include <sstream>

class LineStream
{
	private:
	std::stringstream	_Stream;

	public:
	LineStream(const std::string & text);

	public:
	bool	Continue(std::string & line);
};

#endif
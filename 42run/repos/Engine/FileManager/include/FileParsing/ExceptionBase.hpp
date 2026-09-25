#ifndef  EXCEPTION_BASE_HPP
# define EXCEPTION_BASE_HPP

# include <string>
# include <exception>

class ExceptionBase : public std::exception
{
	protected:
		std::string Text;
	protected:
		ExceptionBase();
	public:
		const char * what() const noexcept;
};

#endif

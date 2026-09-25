#ifndef  BASE_EXCEPTION_HPP
# define BASE_EXCEPTION_HPP

# include <exception>
# include <string>

class TextExceptionBase : public std::exception
{
	protected: std::string Text;
	public: TextExceptionBase();
	public: const char * what() const noexcept;
};

#endif
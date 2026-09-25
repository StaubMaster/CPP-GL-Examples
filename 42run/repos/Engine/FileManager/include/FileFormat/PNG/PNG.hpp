#ifndef  PNG_HPP
# define PNG_HPP

# include "FileInfo.hpp"
# include "Image.hpp"

namespace PNG
{
	Image Load(const FileInfo & file, bool debug = false);

	class PNG_Exception_Signature : public std::exception { public: const char * what() const throw(); };
};

#endif
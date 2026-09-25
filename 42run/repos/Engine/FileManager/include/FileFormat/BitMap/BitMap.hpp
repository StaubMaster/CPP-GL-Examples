#ifndef  BITMAP_HPP
# define BITMAP_HPP

# include "FileInfo.hpp"
# include "Image.hpp"

namespace BitMap
{
	Image	Load(const FileInfo & file);
	void	Save(const FileInfo & file, const Image & img);
};

#endif
#ifndef  TEXTURE_FILE_INDEX_HPP
# define TEXTURE_FILE_INDEX_HPP

# include "FileInfo.hpp"

struct TextureFileIndex
{
	FileInfo		File;
	unsigned int	Index = 0xFFFF;
};

#endif
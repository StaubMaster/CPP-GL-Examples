#ifndef  TEXTURE_FILE_INDEX_HPP
# define TEXTURE_FILE_INDEX_HPP

# include "FileInfo.hpp"

struct TextureFileIndex
{
	FileInfo		File;
	unsigned short	Index = 0xFFFF;

	void	Change(const FileInfo & file);
};

#endif
#ifndef  TEXTURE_FILE_MAP_HPP
# define TEXTURE_FILE_MAP_HPP

# include "Generics/Container/Binary.hpp"

# include "FileInfo.hpp"

struct TextureFileIndex;

struct TextureFileMap
{
	Container::Binary<FileInfo>		Files;

	unsigned int		FindFile(const FileInfo & file) const;
	unsigned int		MakeFile(const FileInfo & file);
	unsigned int		FindMakeFile(const FileInfo & file);

	void	Assign(TextureFileIndex & tex_idx);
};

#endif
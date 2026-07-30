#include "TextureFileMap.hpp"
#include "TextureFileIndex.hpp"



unsigned int TextureFileMap::FindFile(const FileInfo & file) const
{
	for (unsigned int i = 0; i < Files.Count(); i++)
	{
		if (Files[i].Name() == file.Name())
		{
			return i;
		}
	}
	return 0xFFFF;
}
unsigned int TextureFileMap::MakeFile(const FileInfo & file)
{
	unsigned int idx = Files.Count();
	Files.Insert(file);
	return idx;
}
unsigned int TextureFileMap::FindMakeFile(const FileInfo & file)
{
	unsigned int idx = FindFile(file);
	if (idx == 0xFFFF)
	{
		idx = MakeFile(file);
	}
	return idx;
}



void TextureFileMap::Assign(TextureFileIndex & tex_idx)
{
	tex_idx.Index = FindMakeFile(tex_idx.File);
}

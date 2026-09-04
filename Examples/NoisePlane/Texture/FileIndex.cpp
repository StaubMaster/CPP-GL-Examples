#include "Texture/FileIndex.hpp"

void TextureFileIndex::Change(const FileInfo & file)
{
	File = file;
	Index = 0xFFFF;
}

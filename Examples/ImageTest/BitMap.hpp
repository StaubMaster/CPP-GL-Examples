#ifndef  BITMAP_HPP
# define BITMAP_HPP

# include "FileInfo.hpp"
# include "Image.hpp"

Image	LoadBitMap(const FileInfo & file);
void	SaveBitMap(const FileInfo & file, Image & img);

#endif
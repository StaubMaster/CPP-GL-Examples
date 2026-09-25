#include "FileFormat/PNG/IHDR.hpp"
#include "FileParsing/DebugManager.hpp"

#include <sstream>

#include <iostream>



PNG::IHDR::IHDR()
{ }

void PNG::IHDR::Parse(ByteStreamGetter & stream)
{
	width = ReverseBytes(stream.Get4());
	height = ReverseBytes(stream.Get4());

	bit_depth = stream.Get1();
	color_type = stream.Get1();

	compression_method = stream.Get1();
	filter_method = stream.Get1();
	interlace_method = stream.Get1();
}



uint64 PNG::IHDR::UncompressedSize() const
{
	uint8 byte_per_pixel = 0;
	if (color_type == 2) { byte_per_pixel = 3; }
	else if (color_type == 6) { byte_per_pixel = 4; }
	else { return 0; }
	return (width * byte_per_pixel + 1) * height;
}



void PNG::IHDR::ToConsole() const
{
	*DebugManager::Console << " width: " << width << "\n";
	*DebugManager::Console << "height: " << height << "\n";

	*DebugManager::Console << " bit_depth: " << (uint16)bit_depth << "\n";
	*DebugManager::Console << "color_type: " << (uint16)color_type << "\n";

	*DebugManager::Console << "compression_method: " << (uint16)compression_method << "\n";
	*DebugManager::Console << "     filter_method: " << (uint16)filter_method << "\n";
	*DebugManager::Console << "  interlace_method: " << (uint16)interlace_method << "\n";
}

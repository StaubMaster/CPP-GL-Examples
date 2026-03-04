#include "BitMap.hpp"

#include <string>
#include <iostream>

#include "FileParsing/ByteStream.hpp"
#include "ValueType/uint.hpp"



uint8 Get1(ByteStream & stream)
{
	return stream.Data[stream.Index];
}
uint16 Get2(ByteStream & stream)
{
	uint16 data = 0;
	data = (data << 8) | stream.Data[stream.Index + 1];
	data = (data << 8) | stream.Data[stream.Index + 0];
	return data;
}
uint32 Get4(ByteStream & stream)
{
	uint32 data = 0;
	data = (data << 8) | stream.Data[stream.Index + 3];
	data = (data << 8) | stream.Data[stream.Index + 2];
	data = (data << 8) | stream.Data[stream.Index + 1];
	data = (data << 8) | stream.Data[stream.Index + 0];
	return data;
}

void Move(ByteStream & stream, unsigned int move)
{
	stream.Index += move;
}

void LoadRGB(ByteStream & stream, Image & img, uint32 data_size)
{
	ColorU4 col;
	col.A = 0xFF;
	for (uint32 u = 0; u < data_size; u++)
	{
		col.B = stream.Get(); stream.Next();
		col.G = stream.Get(); stream.Next();
		col.R = stream.Get(); stream.Next();
		img.Pixel(u) = col;
	}
}

struct BITMAPINFOHEADER
{
	uint32 ImageSizeW;
	uint32 ImageSizeH;
	uint16 NumberOfColorPlanes; // must be 1
	uint16 NumberOfBitsPerPixel;
	uint32 Compression;
	uint32 ImageDataSize;
	int HoriPixelPerMetre;
	int VertPixelPerMetre;
	uint32 NumberOfColorsInPallet;
	uint32 NumberOfImportantColors;

	BITMAPINFOHEADER(ByteStream & stream)
	{
		ImageSizeW = Get4(stream); Move(stream, 4);
		ImageSizeH = Get4(stream); Move(stream, 4);
		NumberOfColorPlanes = Get2(stream); Move(stream, 2);
		NumberOfBitsPerPixel = Get2(stream); Move(stream, 2);
		Compression = Get4(stream); Move(stream, 4);
		ImageDataSize = Get4(stream); Move(stream, 4);
		HoriPixelPerMetre = Get4(stream); Move(stream, 4);
		VertPixelPerMetre = Get4(stream); Move(stream, 4);
		NumberOfColorsInPallet = Get4(stream); Move(stream, 4);
		NumberOfImportantColors = Get4(stream); Move(stream, 4);

		std::cout << "ImageSizeW" << ' ' << ImageSizeW << '\n';
		std::cout << "ImageSizeH" << ' ' << ImageSizeH << '\n';
		std::cout << "NumberOfColorPlanes" << ' ' << NumberOfColorPlanes << '\n';
		std::cout << "NumberOfBitsPerPixel" << ' ' << NumberOfBitsPerPixel << '\n';
		std::cout << "Compression" << ' ' << Compression << '\n';
		std::cout << "ImageDataSize" << ' ' << ImageDataSize << '\n';
		std::cout << "HoriPixelPerMetre" << ' ' << HoriPixelPerMetre << '\n';
		std::cout << "VertPixelPerMetre" << ' ' << VertPixelPerMetre << '\n';
		std::cout << "NumberOfColorsInPallet" << ' ' << NumberOfColorsInPallet << '\n';
		std::cout << "NumberOfImportantColors" << ' ' << NumberOfImportantColors << '\n';
		std::cout << '\n';
	}

	static bool Parse(ByteStream & stream, Image & img, uint32 & data_size)
	{
		std::cout << "\nBITMAPINFOHEADER\n";
		BITMAPINFOHEADER header(stream);

		bool ret = false;
		if (header.NumberOfColorPlanes != 1)		{ std::cout << "BITMAPINFOHEADER: Unimplemented: NumberOfColorPlanes " << header.NumberOfColorPlanes << ".\n"; ret = true; }
		if (header.NumberOfBitsPerPixel != 24)		{ std::cout << "BITMAPINFOHEADER: Unimplemented: NumberOfBitsPerPixel " << header.NumberOfBitsPerPixel << ".\n"; ret = true; }
		if (header.Compression != 0)				{ std::cout << "BITMAPINFOHEADER: Unimplemented: Compression " << header.Compression << ".\n"; ret = true; }
		if (header.NumberOfColorsInPallet != 0)		{ std::cout << "BITMAPINFOHEADER: Unimplemented: NumberOfColorsInPallet " << header.NumberOfColorsInPallet << ".\n"; ret = true; }
		if (header.NumberOfImportantColors != 0)	{ std::cout << "BITMAPINFOHEADER: Unimplemented: NumberOfImportantColors " << header.NumberOfImportantColors << ".\n"; ret = true; }

		img.Init(header.ImageSizeW, header.ImageSizeH);
		data_size = header.ImageDataSize;
		return ret;
	}
};


Image LoadBitMap(const FileInfo & file)
{
	std::string file_text = file.LoadText();
	Image img;

	ByteStream stream(0);
	stream.Concatenation((const uint8 *)file_text.c_str(), file_text.length());

	{
		uint16 signature = Get2(stream);
		if (signature != 0x4D42)
		{
			std::cout << "LoadBitMap: Error: Bad Signature.\n";
			return img;
		}
		Move(stream, 2);
	}

	uint32 size = Get4(stream);
	std::cout << "LoadBitMap: Size: " << size << '\n';
	Move(stream, 4);

	Move(stream, 2); // Reserved
	Move(stream, 2); // Reserved

	uint32 offset = Get4(stream);
	std::cout << "LoadBitMap: Offset: " << offset << '\n';
	Move(stream, 4);
	
	uint32 header_size = Get4(stream);
	std::cout << "LoadBitMap: Header Size: " << header_size << '\n';
	Move(stream, 4);

	uint32 data_size;
	bool ret = false; // replace with Exception
	switch (header_size)
	{
		case 40:
			ret = BITMAPINFOHEADER::Parse(stream, img, data_size);
			break;
		default:
			std::cout << "LoadBitMap: Error: Unknown Header Size.\n";
			return img;
	}
	if (ret) { return img; }

	stream.Index = offset;
	std::cout << "Idx: " << stream.Index << '\n';
	std::cout << "Len: " << stream.Len << '\n';
	LoadRGB(stream, img, data_size / 3);

	return img;
}



//void SaveBitMap(const FileInfo & file, Image & img)
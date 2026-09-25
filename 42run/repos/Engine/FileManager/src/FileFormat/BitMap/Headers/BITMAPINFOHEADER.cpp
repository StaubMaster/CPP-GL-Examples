#include "FileFormat/BitMap/Headers/BITMAPINFOHEADER.hpp"
#include "FileFormat/BitMap/Exceptions.hpp"

#include <iostream>



BitMap::BITMAPINFOHEADER::BITMAPINFOHEADER(const Image & img, uint32 data_size)
{
	ImageSizeW = img.W();
	ImageSizeH = img.H();
	NumberOfColorPlanes = 1;
	NumberOfBitsPerPixel = 24;
	Compression = 0;
	ImageDataSize = data_size * 3;
	HoriPixelPerMetre = 0;
	VertPixelPerMetre = 0;
	NumberOfColorsInPallet = 0;
	NumberOfImportantColors = 0;
}
BitMap::BITMAPINFOHEADER::BITMAPINFOHEADER(ByteStreamGetter & stream)
{
	ImageSizeW = stream.Get4();
	ImageSizeH = stream.Get4();
	NumberOfColorPlanes = stream.Get2();
	NumberOfBitsPerPixel = stream.Get2();
	Compression = stream.Get4();
	ImageDataSize = stream.Get4();
	HoriPixelPerMetre = stream.Get4();
	VertPixelPerMetre = stream.Get4();
	NumberOfColorsInPallet = stream.Get4();
	NumberOfImportantColors = stream.Get4();
}

void BitMap::BITMAPINFOHEADER::Show() const
{
	std::cout << "\nBITMAPINFOHEADER\n";
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

void BitMap::BITMAPINFOHEADER::Parse(ByteStreamGetter & stream, Image & img, uint32 & data_size)
{
	BITMAPINFOHEADER header(stream);
	//header.Show();

	if (header.NumberOfColorPlanes != 1)		{ throw Exceptions::UnknownHeaderValue("NumberOfColorPlanes", header.NumberOfColorPlanes); }
	if (header.NumberOfBitsPerPixel != 24)		{ throw Exceptions::UnknownHeaderValue("NumberOfBitsPerPixel", header.NumberOfBitsPerPixel); }
	if (header.Compression != 0)				{ throw Exceptions::UnknownHeaderValue("Compression", header.Compression); }
	if (header.NumberOfColorsInPallet != 0)		{ throw Exceptions::UnknownHeaderValue("NumberOfColorsInPallet", header.NumberOfColorsInPallet); }
	if (header.NumberOfImportantColors != 0)	{ throw Exceptions::UnknownHeaderValue("NumberOfImportantColors", header.NumberOfImportantColors); }

	img.Init(header.ImageSizeW, header.ImageSizeH);
	data_size = header.ImageDataSize;
}
void BitMap::BITMAPINFOHEADER::Put(ByteStreamSetter & stream)
{
	stream.Set4(ImageSizeW);
	stream.Set4(ImageSizeH);
	stream.Set2(NumberOfColorPlanes);
	stream.Set2(NumberOfBitsPerPixel);
	stream.Set4(Compression);
	stream.Set4(ImageDataSize);
	stream.Set4(HoriPixelPerMetre);
	stream.Set4(VertPixelPerMetre);
	stream.Set4(NumberOfColorsInPallet);
	stream.Set4(NumberOfImportantColors);
}

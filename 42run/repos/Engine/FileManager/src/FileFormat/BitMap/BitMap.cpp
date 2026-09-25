#include "FileFormat/BitMap/BitMap.hpp"
#include "FileFormat/BitMap/Exceptions.hpp"
#include "FileFormat/BitMap/Headers/BITMAPINFOHEADER.hpp"

#include "FileParsing/ByteBlock.hpp"
#include "FileParsing/ByteStreamGetter.hpp"
#include "FileParsing/ByteStreamSetter.hpp"
#include "uint.hpp"

#include <iostream>



void LoadRGB(ByteStreamGetter & stream, Image & img, uint32 data_size)
{
	ColorU4 col;
	col.A = 0xFF;
	for (uint32 u = 0; u < data_size; u++)
	{
		col.B = stream.Get1();
		col.G = stream.Get1();
		col.R = stream.Get1();
		img.Pixel(u) = col;
	}
}
void SaveRGB(ByteStreamSetter & stream, const Image & img, uint32 data_size)
{
	ColorU4 col;
	for (uint32 u = 0; u < data_size; u++)
	{
		col = img.Pixel(u);
		stream.Set1(col.B);
		stream.Set1(col.G);
		stream.Set1(col.R);
	}
}



Image BitMap::Load(const FileInfo & file)
{
	Image img;
	try
	{
		ByteBlock block(file.LoadBytes());
		ByteStreamGetter stream(block);
		{
			uint16 signature = stream.Get2();
			if (signature != 0x4D42)
			{
				throw Exceptions::UnknownSignature();
			}
			uint32 file_size = stream.Get4();
			(void)file_size; // == stream.Block.Size(). maybe used for stream reading ?
			stream.Move(2); // Reserved
			stream.Move(2); // Reserved
		}

		uint32 data_offset = stream.Get4();
		uint32 data_size;
		uint32 header_size = stream.Get4();
		switch (header_size)
		{
			case 40:
				BITMAPINFOHEADER::Parse(stream, img, data_size);
				break;
			default:
			throw BitMap::Exceptions::UnknownHeader();
		}

		stream.Index = data_offset;
		// data_size / 3 depends on BitsPerPixel being 24
		LoadRGB(stream, img, data_size / 3);
	}
	catch(const std::exception& e)
	{
		std::cerr << "BitMap: Exception while loading Image: " << e.what() << "\n";
		img.Dispose();
	}
	return img;
}



void BitMap::Save(const FileInfo & file, const Image & img)
{
	uint32 data_size = img.W() * img.H();

	ByteBlock data(14 + 40 + data_size * 3);
	ByteStreamSetter stream(data);

	uint64 file_size_idx;
	{
		stream.Set2(0x4D42);
		file_size_idx = stream.Index;
		stream.Move(4);
		stream.Move(2); // Reserved
		stream.Move(2); // Reserved
	}

	uint64 data_offset_idx = stream.Index;
	stream.Move(4);

	stream.Set4(40);
	BITMAPINFOHEADER header(img, data_size);
	header.Put(stream);

	stream.Set4(data_offset_idx, stream.Index);
	SaveRGB(stream, img, data_size);

	stream.Set4(file_size_idx, stream.Index);

	//file.SaveBytes(stream.Block);
	file.SaveBytes(data);
}

#include "FileFormat/PNG/ZLIB.hpp"
#include "FileFormat/PNG/DEFLATE.hpp"

#include "FileParsing/DebugManager.hpp"

#include <iostream>



ZLIB::ZLIB(ByteBlock zlib_block)
{
	ByteStreamGetter stream(zlib_block);

	CMF = stream.Get1();
	FLG = stream.Get1();

	if ((FLG >> 5) & 0b1)
	{
		DICTID = stream.Get4();
		Data = ByteBlock(stream.Block.Length() - 6, stream.Block.DataAt(stream.Index));
	}
	else
	{
		DICTID = 0;
		Data = ByteBlock(stream.Block.Length() - 2, stream.Block.DataAt(stream.Index));
	}

	stream.Move(Data.Length() - 4);
	ADLER32 = stream.Get4(); // maybe check this ?
}

void ZLIB::ToConsole() const
{
	std::cout << AnsiCode::Info << "ZLIB:" << AnsiCode::Done;

	uint8	CM = (CMF >> 0) & 0b1111;
	uint8	CINFO = (CMF >> 4) & 0b1111;
	std::cout << AnsiCode::Info << "CMF    : " << ToBase2(CMF) << AnsiCode::Done;
	std::cout << AnsiCode::Info << "CM     : " << ToBase2(CM, 3) << AnsiCode::Done;
	std::cout << AnsiCode::Info << "CINFO  : " << ToBase2(CINFO, 3) << AnsiCode::Done;

	uint8	FCHECK = (FLG >> 0) & 0b11111;
	uint8	FDICT = (FLG >> 5) & 0b1;
	uint8	FLEVEL = (FLG >> 6) & 0b11;
	std::cout << AnsiCode::Info << "FLG    : " << ToBase2(FLG) << AnsiCode::Done;
	std::cout << AnsiCode::Info << "FCHECK : " << ToBase2(FCHECK, 4) << AnsiCode::Done;
	std::cout << AnsiCode::Info << "FDICT  : " << ToBase2(FDICT, 0) << AnsiCode::Done;
	std::cout << AnsiCode::Info << "FLEVEL : " << ToBase2(FLEVEL, 1) << AnsiCode::Done;

	std::cout << AnsiCode::Info << "DICTID : " << ToBase16(DICTID) << AnsiCode::Done;

	std::cout << AnsiCode::Info << "Length : " << Data.Length() << AnsiCode::Done;

	std::cout << AnsiCode::Info << "ADLER32: " << ToBase16(ADLER32) << AnsiCode::Done;
}



ByteBlock ZLIB::decompress(ByteBlock data, uint64 size)
{
	ZLIB zlib(data);
	//zlib.ToConsole();
	data = DEFLATE::decode(zlib.Data, size);
	return data;
}

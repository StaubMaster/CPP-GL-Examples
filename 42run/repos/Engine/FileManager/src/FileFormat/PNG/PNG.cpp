#include "FileFormat/PNG/PNG.hpp"
#include "FileFormat/PNG/IHDR.hpp"
#include "FileFormat/PNG/Filter.hpp"
#include "FileFormat/PNG/Chunk.hpp"
#include "FileFormat/PNG/ZLIB.hpp"
#include "FileFormat/PNG/Huffman.hpp"
#include "FileFormat/PNG/DEFLATE.hpp"

#include "FileParsing/DebugManager.hpp"

#include "FileParsing/ByteBlock.hpp"
#include "FileParsing/ByteStreamGetter.hpp"
#include "FileParsing/ByteStreamSetter.hpp"
#include "FileParsing/ByteStreamQueue.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>

static ByteBlock PNG_Chunks(ByteBlock data, PNG::IHDR & ImageHeader)
{
	ByteStreamGetter ChunkStream(data);

	{
		uint64 signature_received = ChunkStream.Get8();
		if (signature_received != 0x0A1A0A0D474E5089)
		{
			throw PNG::PNG_Exception_Signature();
		}
	}

	data.Dispose();
	while (1)
	{
		PNG::Chunk chunk(ChunkStream);
		//std::cout << AnsiCode::Debug << "PNG: Chunk: " << AnsiCode::White << uint_Chr(chunk.Type) << AnsiCode::Done;
		if (chunk.CheckCRC())
		{
			if      (chunk.CheckType("IEND"))	{ break; }
			else if (chunk.CheckType("IHDR"))	{ chunk.Parse_IHDR(ImageHeader); }
			else if (chunk.CheckType("IDAT"))	{ chunk.Parse_IDAT(data); }
			else if (chunk.CheckType("tEXt"))	{ chunk.Parse_tEXt(); }
			else { }
		}
		else
		{
			//std::cout << AnsiCode::Error << "PNG: Chunk: invalid CRC Value" << AnsiCode::Done;
			//Throw an Error
		}
	}

	return data;
}

Image PNG::Load(const FileInfo & file, bool debug)
{
	if (debug) { DebugManager::ChangeConsoleToCOut(); }
	else { DebugManager::ChangeConsoleToDump(); }

	try
	{
		ByteBlock data = file.LoadBytes();
		IHDR ImageHeader;
		data = PNG_Chunks(data, ImageHeader);
		//std::cout << AnsiCode::Info << "IDAT Length: " << data.Length() << AnsiCode::Done;
		data = ZLIB::decompress(data, ImageHeader.UncompressedSize());
		return PNG::Filter::filter(ImageHeader, data);
	}
	catch(const std::exception& e)
	{
		//std::cerr << AnsiCode::Error << "PNG: Exception: " << e.what() << AnsiCode::Done;
		//std::cerr << "Exception while loading Image: " << e.what() << "\n";
		return Image();
	}
}



const char * PNG::PNG_Exception_Signature::what() const throw() { return "Bad Signature"; }

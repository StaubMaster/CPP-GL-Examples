#include "FileFormat/PNG/Chunk.hpp"
#include "FileParsing/DebugManager.hpp"
#include "FileFormat/PNG/ErrorDetection.hpp"

#include <sstream>



PNG::Chunk::Chunk(ByteStreamGetter & stream)
	: Length(ReverseBytes(stream.Get4()))
	, CRC_Calc(CRC32(&(stream.Block.Data()[stream.Index]), Length + 4))
	, Type(stream.Get4())
	, Data(&(stream.Block.Data()[stream.Index]))
	, CRC_Read((stream.Move(Length), ReverseBytes(stream.Get4())))
{ }



ByteBlock PNG::Chunk::ToBlock() const
{
	return ByteBlock(Length, Data);
}



bool PNG::Chunk::CheckCRC()
{
	return (CRC_Calc == CRC_Read);
}
bool PNG::Chunk::CheckType(uint8 c0, uint8 c1, uint8 c2, uint8 c3)
{
	return (
		((uint8)(Type >> 0)) == c0 &&
		((uint8)(Type >> 8)) == c1 &&
		((uint8)(Type >> 16)) == c2 &&
		((uint8)(Type >> 24)) == c3
	);
}
bool PNG::Chunk::CheckType(const char * str)
{
	unsigned int len = 0;
	while (str[len] != '\0') { len++; }
	if (len != 4)
	{
		throw "Bad Type Check";
	}
	return CheckType(str[0], str[1], str[2], str[3]);
}



void PNG::Chunk::ToConsole() const
{
	*DebugManager::Console << "PNG Chunk:";
	*DebugManager::Console << ' ' << uint_Chr(Type);
	*DebugManager::Console << ' ' << Length;
	*DebugManager::Console << '\n';
}





void PNG::Chunk::Parse_IHDR(IHDR & ihdr) const
{
	ByteStreamGetter stream(ByteBlock(Length, Data));
	ihdr.Parse(stream);
	ihdr.ToConsole();
}
void PNG::Chunk::Parse_IDAT(ByteBlock & data) const
{
	data.Concatenation(ByteBlock(Length, Data));
}
void PNG::Chunk::Parse_tEXt() const
{
	uint32 text_data_idx = 0;
	const char * text_key = (const char *)Data + text_data_idx;
	uint32 text_key_len = 0;
	while ((text_key[text_key_len] != '\0') && (text_data_idx < Length))
	{
		text_key_len++;
		text_data_idx++;
	}

	text_data_idx++;
	const char * text_value = (const char *)Data + text_data_idx;
	uint32 text_value_len = 0;
	while ((text_value[text_value_len] != '\0') && (text_data_idx < Length))
	{
		text_key_len++;
		text_data_idx++;
	}

	*DebugManager::Console << "Text";
	*DebugManager::Console << " [" << text_key_len << "|" << text_value_len << "] ";
	*DebugManager::Console << "\"" << text_key << "\" \"" << text_value << "\"";
	*DebugManager::Console << " " << text_data_idx << " | " << Length;
	*DebugManager::Console << '\n';
}

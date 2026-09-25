#include "uint.hpp"

//#include <iostream>
#include <sstream>

#define UINT_BIT_CHARS_PER_BYTE 8
#define UINT_HEX_CHARS_PER_BYTE 2

#define  UINT8_SEPERATORS  UINT8_BYTE_COUNT - 1
#define UINT16_SEPERATORS UINT16_BYTE_COUNT - 1
#define UINT32_SEPERATORS UINT32_BYTE_COUNT - 1
#define UINT64_SEPERATORS UINT64_BYTE_COUNT - 1

#define  UINT8_HEX_CHARS UINT_HEX_CHARS_PER_BYTE *  UINT8_BYTE_COUNT
#define UINT16_HEX_CHARS UINT_HEX_CHARS_PER_BYTE * UINT16_BYTE_COUNT
#define UINT32_HEX_CHARS UINT_HEX_CHARS_PER_BYTE * UINT32_BYTE_COUNT
#define UINT64_HEX_CHARS UINT_HEX_CHARS_PER_BYTE * UINT64_BYTE_COUNT

/*static const char * bits_table[] = {
	"00000000", "00000001", "00000010", "00000011", "00000100", "00000101", "00000110", "00000111",
	"00001000", "00001001", "00001010", "00001011", "00001100", "00001101", "00001110", "00001111",
	"00010000", "00010001", "00010010", "00010011", "00010100", "00010101", "00010110", "00010111",
	"00011000", "00011001", "00011010", "00011011", "00011100", "00011101", "00011110", "00011111",
	"00100000", "00100001", "00100010", "00100011", "00100100", "00100101", "00100110", "00100111",
	"00101000", "00101001", "00101010", "00101011", "00101100", "00101101", "00101110", "00101111",
	"00110000", "00110001", "00110010", "00110011", "00110100", "00110101", "00110110", "00110111",
	"00111000", "00111001", "00111010", "00111011", "00111100", "00111101", "00111110", "00111111",
	"01000000", "01000001", "01000010", "01000011", "01000100", "01000101", "01000110", "01000111",
	"01001000", "01001001", "01001010", "01001011", "01001100", "01001101", "01001110", "01001111",
	"01010000", "01010001", "01010010", "01010011", "01010100", "01010101", "01010110", "01010111",
	"01011000", "01011001", "01011010", "01011011", "01011100", "01011101", "01011110", "01011111",
	"01100000", "01100001", "01100010", "01100011", "01100100", "01100101", "01100110", "01100111",
	"01101000", "01101001", "01101010", "01101011", "01101100", "01101101", "01101110", "01101111",
	"01110000", "01110001", "01110010", "01110011", "01110100", "01110101", "01110110", "01110111",
	"01111000", "01111001", "01111010", "01111011", "01111100", "01111101", "01111110", "01111111",
	"10000000", "10000001", "10000010", "10000011", "10000100", "10000101", "10000110", "10000111",
	"10001000", "10001001", "10001010", "10001011", "10001100", "10001101", "10001110", "10001111",
	"10010000", "10010001", "10010010", "10010011", "10010100", "10010101", "10010110", "10010111",
	"10011000", "10011001", "10011010", "10011011", "10011100", "10011101", "10011110", "10011111",
	"10100000", "10100001", "10100010", "10100011", "10100100", "10100101", "10100110", "10100111",
	"10101000", "10101001", "10101010", "10101011", "10101100", "10101101", "10101110", "10101111",
	"10110000", "10110001", "10110010", "10110011", "10110100", "10110101", "10110110", "10110111",
	"10111000", "10111001", "10111010", "10111011", "10111100", "10111101", "10111110", "10111111",
	"11000000", "11000001", "11000010", "11000011", "11000100", "11000101", "11000110", "11000111",
	"11001000", "11001001", "11001010", "11001011", "11001100", "11001101", "11001110", "11001111",
	"11010000", "11010001", "11010010", "11010011", "11010100", "11010101", "11010110", "11010111",
	"11011000", "11011001", "11011010", "11011011", "11011100", "11011101", "11011110", "11011111",
	"11100000", "11100001", "11100010", "11100011", "11100100", "11100101", "11100110", "11100111",
	"11101000", "11101001", "11101010", "11101011", "11101100", "11101101", "11101110", "11101111",
	"11110000", "11110001", "11110010", "11110011", "11110100", "11110101", "11110110", "11110111",
	"11111000", "11111001", "11111010", "11111011", "11111100", "11111101", "11111110", "11111111",
};*/



static const char Base2_Chars[16] = { '0', '1' };
template <typename uint> std::string ToBase2(uint val, uint8 num, uint8 limit)
{
	num = (num & limit) + 1;
	char chars[num];
	uint8 c = 0;
	for (uint8 i = 0; i < num; i++)
	{
		chars[c] = Base2_Chars[(val >> (limit - i)) & 1];
		c++;
	}
	return (std::string(chars, c));
}
template <typename uint> std::string ToSBase2(uint val, char seperator, uint8 num, uint8 limit, uint8 sep_count)
{
	num = (num & limit) + 1;
	char chars[num + sep_count];
	uint8 c = 0;
	for (uint8 i = 0; i < num; i++)
	{
		if (i != 0 && (i & 0b111) == 0)
		{
			chars[c] = seperator;
			c++;
		}
		chars[c] = Base2_Chars[(val >> (limit - i)) & 1];
		c++;
	}
	return (std::string(chars, c));
}



static const char Base16_Chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
template <typename uint> std::string ToBase16(uint val, uint8 char_count)
{
	char chars[char_count];
	uint8 c = 0;
	for (uint8 i = 0; i < char_count; i++)
	{
		chars[c] = Base16_Chars[(val >> (((char_count - i) - 1) * 4)) & 0xF];
		c++;
	}
	return (std::string(chars, c));
}
template <typename uint> std::string ToSBase16(uint val, char seperator, uint8 char_count, uint8 sep_count)
{
	char chars[char_count + sep_count];
	uint8 c = 0;
	for (uint8 i = 0; i < char_count; i++)
	{
		if (i != 0 && (i & 0b1) == 0)
		{
			chars[c] = seperator;
			c++;
		}
		chars[c] = Base16_Chars[(val >> (((char_count - i) - 1) * 4)) & 0xF];
		c++;
	}
	return (std::string(chars, c));
}



template <typename uint> uint ReverseBytes(uint val, uint8 byte_count)
{
	const uint8 * val_ptr = (const uint8 *)&val;

	uint ret = 0;
	uint8 * ret_ptr = (uint8 *)&ret;

	byte_count--;
	for (uint8 i = 0; i <= byte_count; i++)
	{
		ret_ptr[i] = val_ptr[byte_count - i];
	}

	return ret;
}






//	8

std::string	uint_Chr(uint8 val)
{
	std::stringstream ss;

	ss << val;

	return (ss.str());
}

std::string	ToBase2(uint8 val, uint8 num)
{
	return ToBase2<uint8>(val, num, UINT8_BIT_LIMIT);
}
std::string	ToSBase2(uint8 val, char seperator, uint8 num)
{
	return ToSBase2<uint8>(val, seperator, num, UINT8_BIT_LIMIT, UINT8_SEPERATORS);
}
std::string	ToBase16(uint8 val)
{
	return ToBase16<uint8>(val, UINT8_HEX_CHARS);
}
std::string	ToSBase16(uint8 val, char seperator)
{
	return ToSBase16<uint8>(val, seperator, UINT8_HEX_CHARS, UINT8_SEPERATORS);
}

uint8 ReverseBits(uint8 val)
{
	val = ((val & 0xF0F0F0F0) >> 4) | ((val & 0x0F0F0F0F) << 4);
	val = ((val & 0xCCCCCCCC) >> 2) | ((val & 0x33333333) << 2);
	val = ((val & 0xAAAAAAAA) >> 1) | ((val & 0x55555555) << 1);
	return val;
}
uint8 ReverseBytes(uint8 val)
{
	return ReverseBytes<uint8>(val, UINT8_BYTE_COUNT);
}





//	16

std::string	ToBase2(uint16 val, uint8 num)
{
	return ToBase2<uint16>(val, num, UINT16_BIT_LIMIT);
}
std::string	ToSBase2(uint16 val, char seperator, uint8 num)
{
	return ToSBase2<uint16>(val, seperator, num, UINT16_BIT_LIMIT, UINT16_SEPERATORS);
}
std::string	ToBase16(uint16 val)
{
	return ToBase16<uint16>(val, UINT16_HEX_CHARS);
}
std::string	ToSBase16(uint16 val, char seperator)
{
	return ToSBase16<uint16>(val, seperator, UINT16_HEX_CHARS, UINT16_SEPERATORS);
}

uint16 ReverseBits(uint16 val)
{
	val = ((val & 0xFF00FF00) >> 8)  | ((val & 0x00FF00FF) << 8);
	val = ((val & 0xF0F0F0F0) >> 4)  | ((val & 0x0F0F0F0F) << 4);
	val = ((val & 0xCCCCCCCC) >> 2)  | ((val & 0x33333333) << 2);
	val = ((val & 0xAAAAAAAA) >> 1)  | ((val & 0x55555555) << 1);
	return val;
}
uint16 ReverseBytes(uint16 val)
{
	return ReverseBytes<uint16>(val, UINT16_BYTE_COUNT);
}





//	32

std::string	uint_Chr(uint32 val)
{
	std::stringstream ss;

	uint8 * ptr = (uint8 *)&val;
	for (int i = 0; i < 4; i++)
	{
		ss << ptr[i];
	}

	return (ss.str());
}



std::string	ToBase2(uint32 val, uint8 num)
{
	return ToBase2<uint32>(val, num, UINT32_BIT_LIMIT);
}
std::string	ToSBase2(uint32 val, char seperator, uint8 num)
{
	return ToSBase2<uint32>(val, seperator, num, UINT32_BIT_LIMIT, UINT32_SEPERATORS);
}
std::string	ToBase16(uint32 val)
{
	return ToBase16<uint32>(val, UINT32_HEX_CHARS);
}
std::string	ToSBase16(uint32 val, char seperator)
{
	return ToSBase16<uint32>(val, seperator, UINT32_HEX_CHARS, UINT32_SEPERATORS);
}

uint32 ReverseBits(uint32 val)
{
	val = ((val & 0xFFFF0000) >> 16) | ((val & 0x0000FFFF) << 16);
	val = ((val & 0xFF00FF00) >> 8)  | ((val & 0x00FF00FF) << 8);
	val = ((val & 0xF0F0F0F0) >> 4)  | ((val & 0x0F0F0F0F) << 4);
	val = ((val & 0xCCCCCCCC) >> 2)  | ((val & 0x33333333) << 2);
	val = ((val & 0xAAAAAAAA) >> 1)  | ((val & 0x55555555) << 1);
	return val;
}
uint32 ReverseBytes(uint32 val)
{
	return ReverseBytes<uint32>(val, UINT32_BYTE_COUNT);
}





//	64

std::string	ToBase2(uint64 val, uint8 num)
{
	return ToBase2<uint64>(val, num, UINT64_BIT_LIMIT);
}
std::string	ToSBase2(uint64 val, char seperator, uint8 num)
{
	return ToSBase2<uint64>(val, seperator, num, UINT64_BIT_LIMIT, UINT64_SEPERATORS);
}
std::string	ToBase16(uint64 val)
{
	return ToBase16<uint64>(val, UINT64_HEX_CHARS);
}
std::string	ToSBase16(uint64 val, char seperator)
{
	return ToSBase16<uint64>(val, seperator, UINT64_HEX_CHARS, UINT64_SEPERATORS);
}

uint64 ReverseBits(uint64 val)
{
	val = ((val & 0xFFFFFFFF00000000) >> 32) | ((val & 0x00000000FFFFFFFF) << 32);
	val = ((val & 0xFFFF0000FFFF0000) >> 16) | ((val & 0x0000FFFF0000FFFF) << 16);
	val = ((val & 0xFF00FF00FF00FF00) >> 8)  | ((val & 0x00FF00FF00FF00FF) << 8);
	val = ((val & 0xF0F0F0F0F0F0F0F0) >> 4)  | ((val & 0x0F0F0F0F0F0F0F0F) << 4);
	val = ((val & 0xCCCCCCCCCCCCCCCC) >> 2)  | ((val & 0x3333333333333333) << 2);
	val = ((val & 0xAAAAAAAAAAAAAAAA) >> 1)  | ((val & 0x5555555555555555) << 1);
	return val;
}
uint64 ReverseBytes(uint64 val)
{
	return ReverseBytes<uint64>(val, UINT64_BYTE_COUNT);
}



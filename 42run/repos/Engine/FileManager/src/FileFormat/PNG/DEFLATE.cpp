#include "FileFormat/PNG/DEFLATE.hpp"
#include "FileFormat/PNG/Huffman.hpp"

#include "FileParsing/DebugManager.hpp"
#include "FileParsing/BitStreamGetter.hpp"
#include "FileParsing/ByteStreamQueue.hpp"
#include "uint.hpp"

#include <iostream>



static uint32 len_base_extra_bits[] = {
    0, 0, 0, 0, 0, 0, 0, 0, //257 - 264
    1, 1, 1, 1, //265 - 268
    2, 2, 2, 2, //269 - 273 
    3, 3, 3, 3, //274 - 276
    4, 4, 4, 4, //278 - 280
    5, 5, 5, 5, //281 - 284
    0           //285
};

static uint32 len_base[] = {
    3, 4, 5, 6, 7, 8, 9, 10, //257 - 264
    11, 13, 15, 17,          //265 - 268
    19, 23, 27, 31,          //269 - 273
    35, 43, 51, 59,          //274 - 276
    67, 83, 99, 115,         //278 - 280
    131, 163, 195, 227,      //281 - 284
    258                      //285
};

static uint32 dist_base_extra_bits[] = {
    /*0*/ 0, 0, 0, 0, //0-3
    /*1*/ 1, 1,       //4-5
    /*2*/ 2, 2,       //6-7
    /*3*/ 3, 3,       //8-9
    /*4*/ 4, 4,       //10-11
    /*5*/ 5, 5,       //12-13
    /*6*/ 6, 6,       //14-15
    /*7*/ 7, 7,       //16-17
    /*8*/ 8, 8,       //18-19
    /*9*/ 9, 9,       //20-21
    /*10*/ 10, 10,    //22-23
    /*11*/ 11, 11,    //24-25
    /*12*/ 12, 12,    //26-27
    /*13*/ 13, 13,    //28-29
            0 , 0     //30-31 error, they shouldn't occur
};

static uint32 dist_base[] = {
    /*0*/ 1, 2, 3, 4,    //0-3
    /*1*/ 5, 7,          //4-5
    /*2*/ 9, 13,         //6-7
    /*3*/ 17, 25,        //8-9
    /*4*/ 33, 49,        //10-11
    /*5*/ 65, 97,        //12-13
    /*6*/ 129, 193,      //14-15
    /*7*/ 257, 385,      //16-17
    /*8*/ 513, 769,      //18-19
    /*9*/ 1025, 1537,    //20-21
    /*10*/ 2049, 3073,   //22-23
    /*11*/ 4097, 6145,   //24-25
    /*12*/ 8193, 12289,  //26-27
    /*13*/ 16385, 24577, //28-29
           0    , 0      //30-31, error, shouldn't occur
};



void DEFLATE::decode_Huffman(BitStreamGetter & bits, HuffmanTree & literal, HuffmanTree & distance, ByteStreamQueue & data)
{
	//std::cout << AnsiCode::Debug << "Deflate: Block: literal/distance ...." << AnsiCode::Done;

	uint32	decode_value;

	uint32	len_idx;
	uint32	len_len;

	uint32	dist_idx;
	uint32	dist_len;

	while (1)
	{
		decode_value = literal.decode(bits);

		if (decode_value < 256)
		{
			data.Set1(decode_value);
		}
		else if (decode_value == 256)
		{
			break;
		}
		else if (decode_value < 286)
		{
			len_idx = decode_value - 257;
			len_len = len_base[len_idx] + bits.Get32Move(len_base_extra_bits[len_idx]);

			dist_idx = distance.decode(bits);
			dist_len = dist_base[dist_idx] + bits.Get32Move(dist_base_extra_bits[dist_idx]);

			data.SetBlock(data.Block.BlockAt(data.IndexSet - dist_len, len_len));
		}
		else
		{
			*DebugManager::Console << "\e[31mError: Invalid Huffman Decode\e[m\n";
			throw Exception_InvalidData("Huffman Decode: ", decode_value);
		}
	}

	//std::cout << AnsiCode::Debug << "Deflate: Block: literal/distance done" << AnsiCode::Done;
}

uint8 * DEFLATE::dynamic_Huffman(BitStreamGetter & bits, uint32 H_LIT, uint32 H_DIST, uint32 H_CLEN)
{
	uint8 codeLenCodeLenOrder[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
	uint8 codeLenCodeLen[19];
	for (uint32 i = 0; i < 19; i++)
	{
		codeLenCodeLen[i] = 0;
	}
	for (uint32 i = 0; i < H_CLEN; i++)
	{
		codeLenCodeLen[codeLenCodeLenOrder[i]] = bits.Get32Move(3);
	}

	HuffmanTree	Trees(codeLenCodeLen, 19);
	uint8 * Huffman_BitLen_Trees = new uint8[H_LIT + H_DIST];
	for (uint32 i = 0; i < H_LIT + H_DIST; i++)
	{
		Huffman_BitLen_Trees[i] = 0;
	}

	for (uint32 i = 0; i < H_LIT + H_DIST; i++)
	{
		uint32	decode_value = Trees.decode(bits);

		if (decode_value < 16)
		{
			Huffman_BitLen_Trees[i] = decode_value;
		}
		else
		{
			uint32	repeat_count = 0;
			uint8	repeat_data = 0;
			if (decode_value == 16)
			{
				repeat_count = bits.Get32Move(2) + 3;
				repeat_data = Huffman_BitLen_Trees[i - 1];
			}
			else if (decode_value == 17)
			{
				repeat_count = bits.Get32Move(3) + 3;
			}
			else if (decode_value == 18)
			{
				repeat_count = bits.Get32Move(7) + 11;
			}
			else
			{
				throw Exception_InvalidData("Huffman Decode: ", decode_value);
			}

			for (uint32 r = 0; r < repeat_count; r++)
			{
				Huffman_BitLen_Trees[i] = repeat_data;
				i++;
			}
			i--;
		}
	}

	return (Huffman_BitLen_Trees);
}



void DEFLATE::decode_direct(BitStreamGetter & bits, ByteStreamQueue & data)
{
	(void)bits;
	(void)data;
	//*DebugManager::Console << "\e[34mdirect Data ...\e[m\n";
	//std::cout << "\e[34m" << "direct Block .... " << "\e[m\n";

	throw Exception_NotImplemented("direct Block", "");

	//*DebugManager::Console << "\e[34mdirect Data done\e[m\n";
	//std::cout << "\e[34m" << "direct Block .... " << "\e[m\n";
}
void DEFLATE::decode_static(BitStreamGetter & bits, ByteStreamQueue & data)
{
	uint8 literal_bit_lens[288];
	for (unsigned int i = 0; i < 144; i++) { literal_bit_lens[i] = 8; }
	for (unsigned int i = 144; i < 256; i++) { literal_bit_lens[i] = 9; }
	for (unsigned int i = 256; i < 280; i++) { literal_bit_lens[i] = 7; }
	for (unsigned int i = 280; i < 288; i++) { literal_bit_lens[i] = 8; }

	uint8 distance_bit_lens[32];
	for (unsigned int i = 0; i < 32; i++) { distance_bit_lens[i] = 5; }

	HuffmanTree literal(literal_bit_lens, 288);
	HuffmanTree distance(distance_bit_lens, 32);

	DEFLATE::decode_Huffman(bits, literal, distance, data);
}
void DEFLATE::decode_dynamic(BitStreamGetter & bits, ByteStreamQueue & data)
{
	uint32 H_LIT = bits.Get32Move(5) + 257;
	uint32 H_DIST = bits.Get32Move(5) + 1;
	uint32 H_CLEN = bits.Get32Move(4) + 4;

	uint8 * bitLens = DEFLATE::dynamic_Huffman(bits, H_LIT, H_DIST, H_CLEN);

	HuffmanTree literal(&bitLens[0], H_LIT);
	HuffmanTree distance(&bitLens[H_LIT], H_DIST);

	DEFLATE::decode_Huffman(bits, literal, distance, data);

	delete [] bitLens;
}

ByteBlock DEFLATE::decode(ByteBlock data, uint32 size)
{
	BitStreamGetter streamI(data);

	data = ByteBlock(size);
	ByteStreamQueue streamO(data);

	//std::cout << AnsiCode::Debug << "Deflate ...." << AnsiCode::Done;

	uint8	BFINAL;
	uint8	BTYPE;

	do
	{
		BFINAL = streamI.Get32Move(1);
		BTYPE = streamI.Get32Move(2);

		if (BTYPE == 0b00)
		{
			decode_direct(streamI, streamO);
		}
		else if (BTYPE == 0b01)
		{
			//std::cout << AnsiCode::Debug << "Deflate: Block: static ...." << AnsiCode::Done;
			decode_static(streamI, streamO);
			//std::cout << AnsiCode::Debug << "Deflate: Block: static done" << AnsiCode::Done;
		}
		else if (BTYPE == 0b10)
		{
			//std::cout << AnsiCode::Debug << "Deflate: Block: dynamic ...." << AnsiCode::Done;
			decode_dynamic(streamI, streamO);
			//std::cout << AnsiCode::Debug << "Deflate: Block: dynamic done" << AnsiCode::Done;
		}
		else
		{
			throw Exception_InvalidBlockType(BTYPE);
		}
	}
	while (BFINAL == 0);

	//std::cout << AnsiCode::Debug << "Deflate done" << AnsiCode::Done;
	return data;
}





#include <sstream>
/*
	put this here so it dosent slow down compile of above stuff
	should probably put this in a seperate file
	but I want to make a BaseExceptin for these anyway
	that stores text
	this is just to make it compile for now
	also the headers here could use more foreward declate stuff
*/

DEFLATE::Exception_NotImplemented::Exception_NotImplemented(std::string head, std::string name)
{
	std::ostringstream ss("DEFLATE: not implemented: ");
	ss << head;
	ss << name;
	Text = ss.str();
}
const char * DEFLATE::Exception_NotImplemented::what() const noexcept
{
	return Text.c_str();
}

DEFLATE::Exception_InvalidBlockType::Exception_InvalidBlockType(uint32 type)
{
	std::ostringstream ss("DEFLATE: invalid Block Type: ");
	ss << type;
	Text = ss.str();
}
const char * DEFLATE::Exception_InvalidBlockType::what() const noexcept
{
	return Text.c_str();
}

DEFLATE::Exception_InvalidData::Exception_InvalidData(std::string head, uint32 value)
{
	std::ostringstream ss("DEFLATE: invalid Data: ");
	ss << head;
	ss << value;
	Text = ss.str();
}
const char * DEFLATE::Exception_InvalidData::what() const noexcept
{
	return Text.c_str();
}

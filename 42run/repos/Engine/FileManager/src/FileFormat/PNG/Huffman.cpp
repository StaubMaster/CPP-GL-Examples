#include "FileFormat/PNG/Huffman.hpp"

#include "FileParsing/BitStreamGetter.hpp"
#include "FileParsing/DebugManager.hpp"

#include <iostream>
#include <iomanip>



uint8	HuffmanTree::get_max_BitLen(uint8 * codeBitLen, uint32 len)
{
	uint8	maxBit = 0;
	for (uint32 i = 0; i < len; i++)
	{
		if (maxBit < codeBitLen[i])
			maxBit = codeBitLen[i];
	}
	return (maxBit);
}
void	HuffmanTree::get_BitLen_Count(uint32 *codeCount, uint8 * codeBitLen, uint32 len)
{
	for (uint32 i = 0; i < len; i++)
	{
		codeCount[codeBitLen[i]]++;
	}
}
void	HuffmanTree::first_code_for_BitLen(uint32 *firstCodes, uint32 *codeCount, uint32 len)
{
	uint32	code = 0;
	for (uint32 i = 0; i < len; i++)
	{
		code = (code + codeCount[i]) << 1;
		if (codeCount[i + 1] > 0)
			firstCodes[i + 1] = code;
	}
}
void	HuffmanTree::assing_HuffmanCode(uint32 *assignCodes, uint32 *firstCodes, uint8 *codeBitLen, uint32 len)
{
	for (uint32 i = 0; i < len; i++)
	{
		if (codeBitLen[i] != 0)
			assignCodes[i] = firstCodes[codeBitLen[i]]++;
	}
}

HuffmanTree::HuffmanTree(uint8 * codeBitLen, uint32 len)
{
	static uint32 yes = 1;

	Len = len;
	BitLens = codeBitLen;
	Codes = new uint32[Len];
	for (uint32 i = 0; i < Len; i++)
		Codes[i] = 0;

	uint32	maxBitLen = get_max_BitLen(BitLens, Len);
	if (yes == 0)
	{
		std::cout << "maxLen " << maxBitLen << "\n";
		std::cout << "\n";
		for (uint32 i = 0; i < Len; i++)
		{
			if (codeBitLen[i] != 0)
				std::cout << "codeBitLen [" << std::setw(3) << i << "] " << (uint16)codeBitLen[i] << "\n";
		}
		std::cout << "\n";
	}

	uint32 * codeCount = new uint32[maxBitLen + 1];
	uint32 * firstCodes = new uint32[maxBitLen + 1];
	for (uint32 i = 0; i <= maxBitLen; i++)
	{
		codeCount[i] = 0;
		firstCodes[i] = 0;
	}

	get_BitLen_Count(codeCount, BitLens, Len);
	codeCount[0] = 0;
	if (yes == 0)
	{
		for (uint32 i = 0; i <= maxBitLen; i++)
			std::cout << "count [" << std::setw(3) << i << "] " << codeCount[i] << "\n";
		std::cout << "\n";
	}

	first_code_for_BitLen(firstCodes, codeCount, maxBitLen);
	if (yes == 0)
	{
		for (uint32 i = 0; i <= maxBitLen; i++)
			std::cout << "first [" << std::setw(3) << i << "] " << ToBase2(firstCodes[i], i) << "\n";
		std::cout << "\n";
	}

	assing_HuffmanCode(Codes, firstCodes, BitLens, Len);
	if (yes == 0)
	{
		for (uint32 i = 0; i < Len; i++)
		{
			if (codeBitLen[i] != 0)
				std::cout << "assign [" << std::setw(3) << i << "] " << ToBase2(Codes[i], codeBitLen[i]) << "\n";
		}
		std::cout << "\n";
	}

	yes = 1;

	Masks = new uint32[Len];
	for (uint32 i = 0; i < Len; i++)
	{
		Codes[i] = ReverseBits(Codes[i] << (UINT32_BIT_COUNT - BitLens[i]));
		Masks[i] = ~(0xFFFFFFFF << (BitLens[i]));
	}

	delete [] codeCount;
	delete [] firstCodes;
}
HuffmanTree::~HuffmanTree()
{
	delete [] Codes;
	delete [] Masks;
}



uint32	HuffmanTree::decode(BitStreamGetter & bits)
{
	uint32 code32 = bits.Get32();
	for (uint32 i = 0; i < Len; i++)
	{
		if (BitLens[i] != 0)
		{
			if (Codes[i] == (code32 & Masks[i]))
			{
				bits.MoveBit(BitLens[i]);
				return (i);
			}
		}
	}
	return (0);
}



#include <iostream>
void HuffmanTree::ToConsole() const
{
	for (uint32 i = 0; i < Len; i++)
	{
		//*DebugManager::Console << "[" << std::setw(3) << i << "] " << ToBase2(Codes[i], BitLens[i]) << "\n";
		std::cout << "[" << std::setw(3) << i << "] " << ToBase2(Codes[i], BitLens[i]) << "\n";
	}
}

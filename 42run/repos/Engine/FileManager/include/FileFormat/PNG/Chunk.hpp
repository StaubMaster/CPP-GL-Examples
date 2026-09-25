#ifndef  PNG_CHUNKS_HPP
# define PNG_CHUNKS_HPP

# include "uint.hpp"
# include "FileParsing/ByteBlock.hpp"
# include "FileParsing/ByteStreamGetter.hpp"
# include "FileParsing/BitStreamGetter.hpp"

# include "FileFormat/PNG/IHDR.hpp"

namespace PNG
{
struct Chunk
{
	uint32		Length;
	uint32		CRC_Calc;
	uint32		Type;
	uint8 *		Data;
	uint32		CRC_Read;

	Chunk(ByteStreamGetter & stream);

	ByteBlock	ToBlock() const;

	bool	CheckCRC();
	bool	CheckType(uint8 c0, uint8 c1, uint8 c2, uint8 c3);
	bool	CheckType(const char * str);

	void	ToConsole() const;

	void	Parse_IHDR(IHDR & ihdr) const;
	void	Parse_IDAT(ByteBlock & data) const;
	void	Parse_tEXt() const;
};
};

#endif
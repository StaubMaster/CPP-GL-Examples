#ifndef  ZLIB_HPP
# define ZLIB_HPP

# include "uint.hpp"
# include "FileParsing/ByteStreamGetter.hpp"
# include "FileParsing/ByteStreamQueue.hpp"

class ZLIB
{
	public:
	uint8		CMF;
	uint8		FLG;

	uint32		DICTID;

	ByteBlock	Data;

	uint32		ADLER32;

	ZLIB(ByteBlock zlib_block);
	void	ToConsole() const;

	static ByteBlock	decompress(ByteBlock data, uint64 size);
};

#endif

#ifndef  BIT_I_STREAM_BASE_HPP
# define BIT_I_STREAM_BASE_HPP

# include "BitStreamBase.hpp"

#include "uint.hpp"

class BitIStreamBase : public BitStreamBase
{
	public:
		void	SkipToNextByte();
		void	SkipBytes(uint32 count = 1);
		void	SkipBits(uint32 count = 1);

	public:
		uint8	GetBits8(uint32 bit_count = 8);
		uint16	GetBits16(uint32 bit_count = 16);
		uint32	GetBits32(uint32 bit_count = 32);
		uint64	GetBits64(uint32 bit_count = 64);

};

#endif
